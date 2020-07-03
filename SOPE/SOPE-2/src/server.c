#include <stdlib.h>
#include "log.c"
#include "constants.h"
#include "types.h"
#include "cryptography.c"
#include <errno.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>

bank_account_t bank_accounts[MAX_BANK_ACCOUNTS]; // Bank accounts
static int NUM_ACCOUNTS = 0;                     // Bank accounts number <= MAX_BANK_ACCOUNTS

int NUM_THREADS; // Bank offices

int NUM_REQUESTS = 0; // Requests

int slog; //Server log

bool listening = true;

int fifo_server_dummy;     // Server FIFO descriptor for writing
int fifo_server_read_fd;   // Server FIFO descriptor for reading
int fifo_user_fd;          // User FIFO descriptor
char *fifo_user_name = ""; // User FIFO name

sem_t semRequest, semThreads; // Create semaphores
int valRequest, valThreads;   // To get semaphores values

pthread_mutex_t request_lock = PTHREAD_MUTEX_INITIALIZER; // Mutex that controls requests acess
pthread_mutex_t bank_lock = PTHREAD_MUTEX_INITIALIZER;    // Mutex that controls bank acess

tlv_request_t requests[MAX_BANK_ACCOUNTS]; //Requests

bool verifyID(uint32_t id)
{
    pthread_mutex_lock(&bank_lock);
    for (int i = 0; i < NUM_ACCOUNTS; i++)
    {
        if (bank_accounts[i].account_id == id)
        {
            pthread_mutex_unlock(&bank_lock);
            return false;
        }
    }
    pthread_mutex_unlock(&bank_lock);
    return true;
}

int createAccount(uint32_t id, uint32_t balance, char password[MAX_PASSWORD_LEN])
{
    if (!verifyID(id) && id != ADMIN_ACCOUNT_ID)
        return RC_ID_IN_USE;

    bank_account_t account = {
        .account_id = id,
        .balance = balance};
    char *account_salt = getSalt();
    char *account_hash = getHash(password, account_salt);
    strcpy(account.salt, account_salt);
    strcpy(account.hash, account_hash);
    pthread_mutex_lock(&bank_lock);
    bank_accounts[NUM_ACCOUNTS] = account;
    bank_accounts[NUM_ACCOUNTS].balance = balance;
    NUM_ACCOUNTS++;
    pthread_mutex_unlock(&bank_lock);
    return RC_OK;
}

int checkBalance(uint32_t id, int *balance)
{
    if (id == ADMIN_ACCOUNT_ID)
        return RC_OP_NALLOW;
    pthread_mutex_lock(&bank_lock);
    for (int i = 0; i < NUM_ACCOUNTS; i++)
    {
        if (bank_accounts[i].account_id == id)
        {
            *balance = bank_accounts[i].balance;
            pthread_mutex_unlock(&bank_lock);
            return RC_OK;
        }
    }
    pthread_mutex_unlock(&bank_lock);
    return RC_OTHER;
}

int transfer(uint32_t sID, uint32_t dID, uint32_t amount)
{
    if (sID == ADMIN_ACCOUNT_ID)
        return RC_OP_NALLOW;
    if (sID == dID)
        return RC_SAME_ID;
    if (verifyID(dID))
        return RC_ID_NOT_FOUND;
    int s, d;
    // getAccount
    for (int i = 0; i < NUM_ACCOUNTS; i++)
    {
        if (bank_accounts[i].account_id == sID)
        {
            s = i;
        }
        else if (bank_accounts[i].account_id == dID)
        {
            d = i;
        }
    }
    if (bank_accounts[s].balance - amount < MIN_BALANCE)
        return RC_NO_FUNDS;
    if (bank_accounts[d].balance + amount > MAX_BALANCE)
        return RC_TOO_HIGH;
    bank_accounts[s].balance -= amount;
    bank_accounts[d].balance += amount;
    return RC_OK;
}

void readArgs(char *args[])
{
    if (atoi(args[1]) > MAX_BANK_OFFICES)
    {
        printf("Bank offices exceeded maximum value of %d.\n", MAX_BANK_OFFICES);
        exit(1);
    }
    else
    {
        NUM_THREADS = atoi(args[1]);
    }

    if (strlen(args[2]) < MIN_PASSWORD_LEN || strlen(args[2]) > MAX_PASSWORD_LEN)
    {
        printf("Password must be between %d and %d characters.\n", MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
        exit(2);
    }
}

void createServerFIFO()
{
    if (mkfifo(SERVER_FIFO_PATH, 0777) != 0)
    {
        if (errno == EEXIST)
        {
            printf("FIFO - %s - already exists.\n", SERVER_FIFO_PATH);
        }
        else
            printf("Unable to create FIFO - %s\n", SERVER_FIFO_PATH);
        unlink(SERVER_FIFO_PATH);
        exit(3);
    }
}

void openServerFIFO()
{
    int counter = 0;
    do
    {
        fifo_server_read_fd = open(SERVER_FIFO_PATH, O_RDONLY);
        if (fifo_server_read_fd == -1)
        {
            sleep(1);
            counter++;
        }
        if (counter == 5)
        {
            printf("Unable to open FIFO - %s\n", SERVER_FIFO_PATH);
            unlink(SERVER_FIFO_PATH);
            exit(3);
        }

    } while (fifo_server_read_fd == -1);
    fifo_server_dummy = open(SERVER_FIFO_PATH, O_WRONLY);
}

int openReplyFIFO(pid_t pid)
{
    fifo_user_name = malloc(USER_FIFO_PATH_LEN);
    strcpy(fifo_user_name, USER_FIFO_PATH_PREFIX);

    int length = snprintf(NULL, 0, "%d", pid);

    if (length < 5)
    {
        int sizedifference = 5 - length;
        for (int i = 0; i < sizedifference; i++)
        {
            strcat(fifo_user_name, "0");
        }
    }

    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", pid);

    strcat(fifo_user_name, str);
    
    int counter = 0;

    do
    {
        fifo_user_fd = open(fifo_user_name, O_WRONLY);
        if (fifo_user_fd == -1)
        {
            sleep(1);
            counter++;
        }
        if (counter == 6)
        {
            return 1;
        }
    } while (fifo_server_read_fd == -1);

    return 0;
}

bool authRequest(tlv_request_t *request)
{
    char password[MAX_PASSWORD_LEN];
    uint32_t id = request->value.header.account_id;
    strcpy(password, request->value.header.password);

    for (int i = 0; i < NUM_ACCOUNTS; i++)
    {
        if (bank_accounts[i].account_id == id)
        {
            char *hash = getHash(password, bank_accounts[i].salt);

            if (strcmp(hash, bank_accounts[i].hash) == 0)
            {
                return true;
            }
            return false;
        }
    }
    return false;
}

void sendRequest(tlv_request_t *request)
{
    pthread_mutex_lock(&request_lock);
    requests[NUM_REQUESTS] = *request;
    NUM_REQUESTS++;
    pthread_mutex_unlock(&request_lock);
}

void getRequest(tlv_request_t *request)
{
    pthread_mutex_lock(&request_lock);
    *request = requests[NUM_REQUESTS - 1];
    NUM_REQUESTS--;
    pthread_mutex_unlock(&request_lock);
}

int shutdown()
{
    fchmod(fifo_server_read_fd, 0444);
    listening = false;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        sem_post(&semRequest);
    }
    return RC_OK;
}

void *bankOffice(void *thr_arg)
{
    logBankOfficeOpen(slog, *(int *)thr_arg, pthread_self());
    sem_post(&semThreads);
    sem_getvalue(&semThreads, &valThreads);
    logSyncMechSem(slog, *(int *)thr_arg, SYNC_OP_SEM_POST, SYNC_ROLE_CONSUMER, 0, valThreads);

    while (1)
    {
        sem_getvalue(&semRequest, &valRequest);
        logSyncMechSem(slog, *(int *)thr_arg, SYNC_OP_SEM_WAIT, SYNC_ROLE_PRODUCER, 0, valRequest);
        sem_wait(&semRequest);

        if (!listening)
        {
            break;
        }

        tlv_request_t request;
        tlv_reply_t reply;

        getRequest(&request);
        if (authRequest(&request))
        {

            reply.type = request.type;
            reply.length = sizeof(uint32_t) + sizeof(ret_code_t);
            switch (request.type)
            {
            case OP_CREATE_ACCOUNT:
                if (usleep(request.value.header.op_delay_ms * 1000) == 0)
                {
                    logDelay(slog, *(int *)thr_arg, request.value.header.op_delay_ms);
                    int ret_code = createAccount(request.value.create.account_id, request.value.create.balance, request.value.create.password);
                    reply.value.header.ret_code = ret_code;
                    if (ret_code == RC_OK)
                        logAccountCreation(slog, *(int *)thr_arg, &bank_accounts[NUM_ACCOUNTS - 1]);
                }

                reply.value.header.account_id = *(int *)thr_arg;

                break;

            case OP_BALANCE:
                if (usleep(request.value.header.op_delay_ms * 1000) == 0)
                {
                    int balance = 0;
                    int ret_code = checkBalance(request.value.header.account_id, &balance);
                    reply.value.header.ret_code = ret_code;
                    reply.value.header.account_id = *(int *)thr_arg;
                    if (ret_code == RC_OK) {
                        reply.length += sizeof(uint32_t);
                        reply.value.balance.balance = balance;
                    }
                }
                break;

            case OP_TRANSFER:
                if (usleep(request.value.header.op_delay_ms * 1000) == 0)
                {
                    int ret_code = transfer(request.value.header.account_id, request.value.transfer.account_id, request.value.transfer.amount);
                    reply.value.header.ret_code = ret_code;
                    reply.value.header.account_id = *(int *)thr_arg;
                    if (ret_code == RC_OK) {
                        reply.length += sizeof(uint32_t);
                        reply.value.transfer.balance = bank_accounts[request.value.header.account_id].balance;
                    }
                }
                break;

            case OP_SHUTDOWN:
                if (usleep(request.value.header.op_delay_ms * 1000) == 0)
                {
                    if (request.value.header.account_id == ADMIN_ACCOUNT_ID)
                    {
                        int ret_code = shutdown();
                        reply.value.header.ret_code = ret_code;
                    }
                    else
                    {
                        reply.value.header.ret_code = RC_OP_NALLOW;
                    }
                    if (reply.value.header.ret_code == RC_OK) {
                        reply.value.shutdown.active_offices = NUM_THREADS;
                        reply.length += sizeof(uint32_t);
                    }
                }
                break;
            case __OP_MAX_NUMBER:
                reply.value.header.ret_code = RC_OTHER;
                break;
            }
        }
        else
        {
            reply.value.header.ret_code = RC_LOGIN_FAIL;
        }
        int replyFlag = openReplyFIFO(request.value.header.pid);

        if (replyFlag == 1)
            reply.value.header.ret_code = RC_USR_DOWN;
        logRequest(slog, request.value.header.pid, &request);
        logReply(slog, *(int *)thr_arg, &reply);

        if (replyFlag == 0)
        {
            write(fifo_user_fd, &reply, sizeof(tlv_reply_t));
            close(fifo_user_fd);
        }
        sem_post(&semThreads);

        sem_getvalue(&semThreads, &valThreads);
        logSyncMechSem(slog, *(int *)thr_arg, SYNC_OP_SEM_POST, SYNC_ROLE_CONSUMER, 0, valThreads);
    }
    logBankOfficeClose(slog, *(int *)thr_arg, pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    //Check arguments
    if (argc != 3)
    {
        printf("Usage: %s <bank_offices> <admin_pass>\n", argv[0]);
        return 1;
    }

    slog = open("slog.txt", O_WRONLY | O_APPEND | O_CREAT, 0777); //Open "slog.txt" as server log file

    readArgs(argv); //sProcess arguments

    logSyncMech(slog, MAIN_THREAD_ID, SYNC_OP_MUTEX_LOCK, SYNC_ROLE_ACCOUNT, 0);
    createAccount(ADMIN_ACCOUNT_ID, 0, argv[2]); //Create admin account
    logAccountCreation(slog, MAIN_THREAD_ID, &bank_accounts[ADMIN_ACCOUNT_ID]);
    logSyncMech(slog, MAIN_THREAD_ID, SYNC_OP_MUTEX_UNLOCK, SYNC_ROLE_ACCOUNT, 0);

    pthread_t bank_offices[NUM_THREADS]; //Bank Offices - Threads
    int thr_arg[NUM_THREADS];            //Thread argument

    sem_init(&semThreads, 0, 0);
    sem_getvalue(&semThreads, &valThreads);
    logSyncMechSem(slog, MAIN_THREAD_ID, SYNC_OP_SEM_INIT, SYNC_ROLE_PRODUCER, 0, valThreads);

    sem_init(&semRequest, 0, 0);
    sem_getvalue(&semRequest, &valRequest);
    logSyncMechSem(slog, MAIN_THREAD_ID, SYNC_OP_SEM_INIT, SYNC_ROLE_PRODUCER, 0, valRequest);

    //Create threads
    for (int i = 1; i <= NUM_THREADS; i++)
    {
        thr_arg[i] = i;
        if (pthread_create(&bank_offices[i], NULL, bankOffice, &thr_arg[i]) != 0)
        {
            printf("Unable to create thread %d.\n", i);
            exit(4);
        }
    }
    printf("Server starting.\n");

    createServerFIFO(); //Create Server FIFOs
    openServerFIFO();   //Open Server FIFOs

    while (listening)
    {
        tlv_request_t request;

        if (read(fifo_server_read_fd, &request, sizeof(tlv_request_t)) > 0)
        {
            sem_getvalue(&semThreads, &valThreads);
            logSyncMechSem(slog, MAIN_THREAD_ID, SYNC_OP_SEM_WAIT, SYNC_ROLE_PRODUCER, pthread_self(), valThreads);
            sem_wait(&semThreads);

            sendRequest(&request);
            sem_post(&semRequest);
            sem_getvalue(&semRequest, &valRequest);
            logSyncMechSem(slog, MAIN_THREAD_ID, SYNC_OP_SEM_POST, SYNC_ROLE_PRODUCER, pthread_self(), valRequest);
            if (request.type == OP_SHUTDOWN)
            {
                usleep(100 * 1000);
                usleep(request.value.header.op_delay_ms * 1000);
            }
        }
    }

    printf("Server terminating.\n");

    sem_destroy(&semRequest);
    sem_destroy(&semThreads);

    pthread_mutex_destroy(&request_lock);
    pthread_mutex_destroy(&bank_lock);

    close(fifo_server_dummy);
    close(fifo_server_read_fd);

    unlink(SERVER_FIFO_PATH);

    return 0;
}

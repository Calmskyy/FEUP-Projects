#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "log.c"
#include "constants.h"

int ulog; //User log

int client_id;
char client_password[MAX_PASSWORD_LEN + 1];
int delay;
int operation;

char *arguments;
char *firstArgument;
char *secondArgument;
char *thirdArgument;

int idArgument;
int moneyArgument;
char passwordArgument[MAX_PASSWORD_LEN + 1];

int main(int argc, char *argv[])
{
    //Check arguments
    if (argc != 6)
    {
        printf("Usage: %s <client_ID> <client_password> <delay(ms)> <operation_code> <arguments_string>\n", argv[0]);
        return 1;
    }

    readArgs(argv); //Process arguments

    ulog = open(USER_LOGFILE, O_WRONLY | O_APPEND | O_CREAT, 0777); //Open "ulog.txt" as user log file

    char *fifo_name = createUserFIFO(); //Create FIFO to recieve reply

    req_header_t header = createHeader();
    req_value_t value;
    tlv_request_t request;

    switch (operation)
    {
    case OP_CREATE_ACCOUNT:
        value = createAccountCreationValue(header);
        request = createAccountCreationRequest(value);
        break;
    case OP_BALANCE:
        value = createBlankValue(header);
        request = createBalanceRequest(value);
        break;
    case OP_TRANSFER:
        value = createTransferValue(header);
        request = createTransferRequest(value);
        break;
    case OP_SHUTDOWN:
        value = createBlankValue(header);
        request = createShutdownRequest(value);
        break;
    }

    logRequest(ulog, getpid(), &request);

    int server_fifo = open(SERVER_FIFO_PATH, O_WRONLY);
    if (server_fifo < 0)
    {
        tlv_reply_t reply;
        reply.type = request.type;
        reply.value.header.ret_code = RC_SRV_DOWN;
        reply.length = sizeof(op_type_t) + sizeof(ret_code_t);
        if (operation == OP_BALANCE)
        {
            reply.value.balance.balance = 0;
            reply.length += sizeof(uint32_t);
        }
        else if (operation == OP_TRANSFER)
        {
            reply.value.transfer.balance = 0;
            reply.length += sizeof(uint32_t);
        }
        else if (operation == OP_SHUTDOWN)
        {
            reply.value.shutdown.active_offices = 0;
            reply.length += sizeof(uint32_t);
        }

        printError(reply.value.header.ret_code);
        logReply(ulog, getpid(), &reply);

        unlink(fifo_name);
        free(fifo_name);
        exit(3);
    }

    int write_msg = write(server_fifo, &request, sizeof(tlv_request_t));
    if (write_msg < 0)
    {
        fprintf(stderr, "Failed to write the server request.\n");
        unlink(fifo_name);
        free(fifo_name);
        exit(4);
    }

    tlv_reply_t reply;

    int user_fifo = open(fifo_name, O_RDONLY);
    if (user_fifo < 0)
    {
        fprintf(stderr, "Failed to open user FIFO.\n");
        unlink(fifo_name);
        free(fifo_name);
        exit(3);
    }

    struct timespec start, stop;
    double result = 0;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    while (true)
    {
        int read_msg = read(user_fifo, &reply, sizeof(tlv_reply_t));
        if (read_msg > 0)
            break;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
        result = (stop.tv_sec - start.tv_sec);
        if (result >= FIFO_TIMEOUT_SECS)
        {
            tlv_reply_t reply;
            reply.type = request.type;
            reply.value.header.ret_code = RC_SRV_TIMEOUT;
            reply.length = sizeof(op_type_t) + sizeof(ret_code_t);
            if (operation == OP_BALANCE)
            {
                reply.value.balance.balance = 0;
                reply.length += sizeof(uint32_t);
            }
            else if (operation == OP_TRANSFER)
            {
                reply.value.transfer.balance = 0;
                reply.length += sizeof(uint32_t);
            }
            else if (operation == OP_SHUTDOWN)
            {
                reply.value.shutdown.active_offices = 0;
                reply.length += sizeof(uint32_t);
            }
            break;
        }
    }

    logReply(ulog, getpid(), &reply);

    if (reply.value.header.ret_code != RC_OK)
        printError(reply.value.header.ret_code);

    if (reply.value.header.ret_code == RC_OK)
    {
        switch (operation)
        {
        case OP_CREATE_ACCOUNT:
            printf("Account %d created with starting balance: %d€\n", request.value.create.account_id, request.value.create.balance);
            break;
        case OP_BALANCE:
            printf("User's account balance: %d€\n", reply.value.balance.balance);
            break;
        case OP_TRANSFER:
            printf("Transferred %d€ from account %d to account %d\n", request.value.transfer.amount, request.value.header.account_id, request.value.transfer.account_id);
            break;
        case OP_SHUTDOWN:
            printf("Ordered server shutdown.\n");
            break;
        }
    }

    close(server_fifo);
    close(user_fifo);

    unlink(fifo_name);
    free(fifo_name);

    return 0;
}

void checkNumberBounds(int number, int lowerBound, int higherBound, char *name)
{
    if (number >= lowerBound && number < higherBound)
        return;
    else if (number < lowerBound)
        printf("%s must be equal or bigger than %d\n", name, lowerBound);
    else if (number >= higherBound)
        printf("%s must be smaller than %d\n", name, higherBound);

    exit(1);
}

void checkNumericalString(char string[], char *name)
{
    for (unsigned int i = 0; i < strlen(string); i++)
    {
        if (isdigit(string[i]))
            continue;
        else
        {
            printf("%s must be composed of numbers only.\n", name);
            exit(1);
        }
    }
}

void separateArgs()
{
    char *separation;
    int length;
    int error = 0;
    int n;
    if (operation == OP_CREATE_ACCOUNT)
        n = 3;
    else if (operation == OP_TRANSFER)
        n = 2;

    for (int i = 1; i < n; i++)
    {
        separation = strchr(arguments, ' ');
        if (separation == NULL)
        {
            error = 1;
            break;
        }
        length = strlen(arguments) - strlen(separation);
        if (length > 35)
        {
            printf("Additional arguments (too big to make sense) usage: <new_account_id> <initial_balance> <password>\n");
            exit(1);
        }
        if (i == 1)
        {
            strncpy(firstArgument, arguments, length);
            strcat(firstArgument, "\0");
        }
        else if (i == 2)
        {
            strncpy(secondArgument, arguments, length);
            strcat(secondArgument, "\0");
        }
        separation++;
        arguments = separation;
    }

    if (n == 2)
        secondArgument = separation;
    else if (n == 3)
        thirdArgument = separation;

    if (separation != NULL)
    {
        separation = strchr(separation, ' ');
        if (separation != NULL)
            error = 1;
    }

    if (error == 1 && operation == OP_CREATE_ACCOUNT)
    {
        printf("Additional arguments usage: <new_account_id> <initial_balance> <password>\n");
        exit(1);
    }
    else if (error == 1 && operation == OP_TRANSFER)
    {
        printf("Additional arguments usage: <receiving_account_id> <amount_transferred> \n");
        exit(1);
    }
}

void getAccountCreationArgs()
{
    checkNumericalString(firstArgument, "New account ID");
    idArgument = strtol(firstArgument, NULL, 10);
    checkNumberBounds(idArgument, 0, MAX_BANK_ACCOUNTS, "New account ID");

    checkNumericalString(secondArgument, "Initial balance");
    moneyArgument = strtol(secondArgument, NULL, 10);
    //checkNumberBounds(client_id, MIN_BALANCE, MAX_BALANCE + 1, "Initial balance");

    if (strlen(thirdArgument) < MIN_PASSWORD_LEN || strlen(thirdArgument) > MAX_PASSWORD_LEN)
    {
        printf("Password (additional argument) must be between %d and %d characters.\n", MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
        exit(1);
    }

    for (unsigned int i = 0; i < strlen(thirdArgument); i++)
    {
        if (thirdArgument[i] == ' ')
        {
            printf("Password (additional argument) shouldn't contain any spaces.\n");
            exit(1);
        }
    }

    strncpy(passwordArgument, thirdArgument, MAX_PASSWORD_LEN + 1);
}

void getTransferArgs()
{
    checkNumericalString(firstArgument, "Receiving account ID");
    idArgument = strtol(firstArgument, NULL, 10);
    checkNumberBounds(idArgument, 0, MAX_BANK_ACCOUNTS, "Receiving account ID");

    checkNumericalString(secondArgument, "Amount transferred");
    moneyArgument = strtol(secondArgument, NULL, 10);
    checkNumberBounds(client_id, MIN_BALANCE, MAX_BALANCE + 1, "Amount transferred");
}

void readArgs(char *args[])
{
    checkNumericalString(args[1], "Client ID");
    client_id = strtol(args[1], NULL, 10);
    checkNumberBounds(client_id, 0, MAX_BANK_ACCOUNTS, "Client ID");

    if (strlen(args[2]) < MIN_PASSWORD_LEN || strlen(args[2]) > MAX_PASSWORD_LEN)
    {
        printf("Password must be between %d and %d characters.\n", MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
        exit(1);
    }

    for (unsigned int i = 0; i < strlen(args[2]); i++)
    {
        if (args[2][i] == ' ')
        {
            printf("Password shouldn't contain any spaces.\n");
            exit(1);
        }
    }

    strncpy(client_password, args[2], MAX_PASSWORD_LEN + 1);

    checkNumericalString(args[3], "Operation delay");
    delay = strtol(args[3], NULL, 10);
    checkNumberBounds(delay, 0, MAX_OP_DELAY_MS + 1, "Operation delay");

    checkNumericalString(args[4], "Operation code");
    operation = strtol(args[4], NULL, 10);
    checkNumberBounds(operation, 0, __OP_MAX_NUMBER, "Operation code");

    arguments = args[5];

    if (operation == OP_BALANCE || operation == OP_SHUTDOWN)
    {
        if (strlen(arguments) != 0)
        {
            printf("Checking balance and requesting shutdown take no arguments.\n");
            printf("Input an empty string instead.(\"\")\n");
            exit(1);
        }
    }
    else if (operation == OP_CREATE_ACCOUNT)
    {
        firstArgument = malloc(40);
        secondArgument = malloc(40);
        thirdArgument = malloc(40);
        separateArgs();
        getAccountCreationArgs();
    }
    else if (operation == OP_TRANSFER)
    {
        firstArgument = malloc(40);
        secondArgument = malloc(40);
        thirdArgument = malloc(40);
        separateArgs();
        getTransferArgs();
    }
}

char *createUserFIFO()
{
    char *fifo_name = malloc(USER_FIFO_PATH_LEN);
    strcpy(fifo_name, USER_FIFO_PATH_PREFIX);

    int pid = getpid();

    int length = snprintf(NULL, 0, "%d", pid);

    if (length < 5)
    {
        int sizedifference = 5 - length;
        for (int i = 0; i < sizedifference; i++)
        {
            strcat(fifo_name, "0");
        }
    }
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", pid);

    strcat(fifo_name, str);
    if (mkfifo(fifo_name, 0777) != 0)
    {
        if (errno == EEXIST)
        {
            printf("FIFO - %s - already exists.\n", fifo_name);
        }
        else
            printf("Unable to create FIFO - %s\n", fifo_name);
        free(str);
        unlink(fifo_name);
        free(fifo_name);
        exit(3);
    }
    free(str);
    return fifo_name;
}

req_header_t createHeader()
{
    req_header_t header;

    header.pid = getpid();
    header.op_delay_ms = delay;
    header.account_id = client_id;
    strcpy(header.password, client_password);

    return header;
}

req_value_t createTransferValue(req_header_t header)
{
    req_transfer_t transfer;

    transfer.account_id = idArgument;
    transfer.amount = moneyArgument;

    req_value_t value;

    value.transfer = transfer;
    value.header = header;

    return value;
}

req_value_t createBlankValue(req_header_t header)
{
    req_value_t value;

    value.header = header;

    return value;
}

req_value_t createAccountCreationValue(req_header_t header)
{
    req_create_account_t create;

    create.account_id = idArgument;
    create.balance = moneyArgument;
    strncpy(create.password, passwordArgument, MAX_PASSWORD_LEN + 1);

    req_value_t value;

    value.create = create;
    value.header = header;

    return value;
}

tlv_request_t createBalanceRequest(req_value_t value)
{
    tlv_request_t request;

    request.type = OP_BALANCE;
    request.length = sizeof(op_type_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(pid_t) + sizeof(client_password);
    request.value = value;

    return request;
}

tlv_request_t createAccountCreationRequest(req_value_t value)
{
    tlv_request_t request;

    request.type = OP_CREATE_ACCOUNT;
    request.length = sizeof(op_type_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(pid_t) + sizeof(client_password) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(client_password);
    request.value = value;

    return request;
}

tlv_request_t createTransferRequest(req_value_t value)
{
    tlv_request_t request;

    request.type = OP_TRANSFER;
    request.length = sizeof(op_type_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(pid_t) + sizeof(client_password) + sizeof(uint32_t) + sizeof(uint32_t);
    request.value = value;

    return request;
}

tlv_request_t createShutdownRequest(req_value_t value)
{
    tlv_request_t request;

    request.type = OP_SHUTDOWN;
    request.length = sizeof(op_type_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(pid_t) + sizeof(client_password);
    request.value = value;

    return request;
}

void printError(ret_code_t code)
{
    switch (code)
    {
    case RC_SRV_DOWN:
        printf("Couldn't connect to the server (server is unavailable).\n");
        break;
    case RC_SRV_TIMEOUT:
        printf("Server request timed out. (30 seconds limit).\n");
        break;
    case RC_LOGIN_FAIL:
        printf("Account ID and passwords don't match (no such account on the server).\n");
        break;
    case RC_OP_NALLOW:
        if (client_id == 0)
            printf("This user is the administrator, cannot perform that operation.\n");
        else
            printf("This user is a client, cannot perform that operation.\n");
        break;
    case RC_ID_IN_USE:
        printf("An account with that ID already exists.\n");
        break;
    case RC_ID_NOT_FOUND:
        printf("There's no destination account with that ID to perform the transfer.\n");
        break;
    case RC_SAME_ID:
        printf("Both the source and destination accounts have the same ID, cannot perform transfer\n");
        break;
    case RC_NO_FUNDS:
        printf("The source account does not have enough money to perform the transfer.\n");
        break;
    case RC_TOO_HIGH:
        printf("The destination account does not have enough money to receive the transfer.\n");
        break;
    case RC_OTHER:
        printf("An unspecified error has occurred.\n");
        break;
    case RC_OK:
        break;
    case RC_USR_DOWN:
        break;
    case __RC_MAX_NUMBER:
        break;
    }
}

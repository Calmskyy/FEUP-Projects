#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "dataLinkLayer.h"
#include "utils.c"

#define BAUDRATE_FAST B38400
#define BAUDRATE_MEDIUM B19200
#define BAUDRATE_SLOW B4800
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

#define START 0
#define FLAG_RCV 1
#define A_RCV 2
#define C_RCV 3
#define BCC_OK 4
#define END 5

#define FLAG 0x7E
#define ESC 0x7D
#define STUFFING 0x20
#define A 0x03
#define A1 0x03
#define A2 0x01
#define SET 0x03
#define UA 0x07
#define DISC 0x0B

#define HEADERSIZE 4
#define FOOTERSIZE 3

#define RR_ONE 0x85
#define RR_ZERO 0x05
#define REJ_ONE 0x81
#define REJ_ZERO 0x01

#define RECEIVER 0
#define TRANSMITTER 1

static struct termios oldtio;
static int destuffEscape = FALSE;

volatile int STOP = FALSE;
volatile int nSentSuccesfull = 0;

static DataLinkLayer *dataLink;

void initDataLinkLayer(int porta, int type, int baudRate, int dataSize, int retries, int timeout, int delay, int random)
{
    dataLink = malloc(sizeof(DataLinkLayer));
    snprintf(dataLink->port, 11, "/dev/ttyS%d", porta);
    dataLink->status = type;
    dataLink->baudRate = baudRate;
    dataLink->numTransmissions = retries;
    dataLink->timeout = timeout;
    dataLink->T_prop = delay;
    dataLink->fer = random;
    dataLink->maxFrameSize = HEADERSIZE + 4 + dataSize * 2 + FOOTERSIZE;
}

void alarmHandler(int signal)
{
    if (signal != SIGALRM)
    {
        printf("disconnected\n");
        sleep(3);
        printf("connected\n");
        return;
    }

    STOP = TRUE;
    printf("TIME OUT\n");
}
void setDisconnect()
{
    struct sigaction action;
    memset(&action, 0, sizeof action);
    action.sa_handler = alarmHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);
}

void unsetDisconect()
{
    struct sigaction action;
    action.sa_handler = NULL;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, NULL);
}

void setAlarm()
{
    struct sigaction action;
    memset(&action, 0, sizeof action);
    action.sa_handler = alarmHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, NULL);
}

void unsetAlarm()
{
    STOP = FALSE;
    struct sigaction action;
    action.sa_handler = NULL;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, NULL);
    alarm(0);
}

int sendControlFrame(int fd, char controlField)
{
    unsigned char set[5];
    set[0] = FLAG;

    // (0x03) em Comandos enviados pelo Emissor e Respostas enviadas pelo Receptor
    // (0x01) em Comandos enviados pelo Receptor e Respostas enviadas pelo Emissor
    if (dataLink->status == RECEIVER)
    {
        if (controlField == SET || controlField == DISC)
            set[1] = A2;
        else
            set[1] = A1;
    }
    else if (dataLink->status == TRANSMITTER)
    {
        if (controlField == SET || controlField == DISC)
            set[1] = A1;
        else
            set[1] = A2;
    }

    set[2] = controlField;
    set[3] = set[1] ^ set[2];
    set[4] = FLAG;
    return write(fd, set, 5);
}

int checkControlFrame(int fd, char controlField)
{
    unsigned char c;
    int state = START;
    unsigned char c_received;
    unsigned char expectedAddress;

    if (dataLink->status == RECEIVER)
    {
        if (controlField == SET || controlField == DISC)
            expectedAddress = A1;
        else
            expectedAddress = A2;
    }
    else if (dataLink->status == TRANSMITTER)
    {
        if (controlField == SET || controlField == DISC)
            expectedAddress = A2;
        else
            expectedAddress = A1;
    }

    STOP = FALSE;
    simulateDelay(dataLink->T_prop);

    while (STOP == FALSE)
    {
        c = 0;
        read(fd, &c, 1);

        switch (state)
        {
        case START:
            if (c == FLAG)
                state = FLAG_RCV;
            break;
        case FLAG_RCV:
            if (c == expectedAddress)
                state = A_RCV;
            else
                state = START;
            break;
        case A_RCV:
            if ((c_received = c) == controlField)
            {
                state = C_RCV;
            }
            else if (c == FLAG)
                state = FLAG_RCV;
            else
                return -1;
        case C_RCV:
            if (c == FLAG)
                state = FLAG_RCV;
            else if (c == expectedAddress ^ c_received)
                state = BCC_OK;
            else
                state = START;
            break;
        case BCC_OK:
            if (c == FLAG)
            {
                return 0;
                STOP = TRUE;
                break;
            }
        }
    }
    return -1;
}

int readControlFrame(int fd)
{
    unsigned char c;
    int state = START;
    unsigned char c_received;

    STOP = FALSE;

    simulateDelay(dataLink->T_prop);
    while (STOP == FALSE)
    {
        c = 0;
        read(fd, &c, 1);

        switch (state)
        {
        case START:
            if (c == FLAG)
                state = FLAG_RCV;
            break;
        case FLAG_RCV:
            if (c == A)
                state = A_RCV;
            else
                state = START;
            break;
        case A_RCV:
            if ((c_received = c) == c & SET || c == c & DISC || c == c & UA || c == c & RR_ONE || c == c & REJ_ONE)
            {
                state = C_RCV;
            }
            else if (c == FLAG)
                state = FLAG_RCV;
            else
                state = START;
            break;
        case C_RCV:
            if (c == FLAG)
                state = FLAG_RCV;
            else if (c == A ^ c_received)
                state = BCC_OK;
            else
                state = START;
            break;
        case BCC_OK:
            if (c == FLAG)
            {
                return c_received;
                STOP = TRUE;
                break;
            }
        }
    }
    return -1;
}

int openPort()
{
    struct termios newtio;
    int fd = open(dataLink->port, O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        perror("open port");
        exit(-1);
    }

    if (tcgetattr(fd, &oldtio) == -1)
    { /* save current port settings */
        perror("tcgetattr");
        exit(-1);
    }

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = getBaudRate(dataLink->baudRate) | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME] = 0; /* inter-character timer unused */
    newtio.c_cc[VMIN] = 1;  /* blocking read until 1 chars received */

    tcflush(fd, TCIOFLUSH);

    if (tcsetattr(fd, TCSANOW, &newtio) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    return fd;
}

int llopen(int porta, int type)
{
    setDisconnect();

    int fd = openPort();

    int tries = 0;

    if (dataLink->status == TRANSMITTER)
    {
        while (tries++ < dataLink->numTransmissions)
        {
            setAlarm();
            if (sendControlFrame(fd, SET) > 0)
            {
                alarm(dataLink->timeout);
                if (checkControlFrame(fd, UA) == 0)
                    return fd;
            }
            unsetAlarm();
        }
    }
    else if (dataLink->status == RECEIVER)
    {
        if (checkControlFrame(fd, SET) == 0 && sendControlFrame(fd, UA) > 0)
            return fd;
    }
    else
        return -2;

    return -1;
}

void closeTransmitter(int fd)
{
    int numtries = 0;
    setAlarm();
    do
    {
        sendControlFrame(fd, DISC);
        alarm(dataLink->timeout);
        if (checkControlFrame(fd, DISC) == 0)
        {
            sendControlFrame(fd, UA);
            sleep(1); //give time for receiver to read UA, before closing connection
            break;
        }
        numtries++;
    } while (numtries < dataLink->numTransmissions);
    unsetAlarm();
}

void closeReceiver(int fd)
{
    int numtries = 0;
    setAlarm();
    do
    {
        if (checkControlFrame(fd, DISC) == 0)
        {
            sendControlFrame(fd, DISC);
            alarm(dataLink->timeout);
            if (checkControlFrame(fd, UA) == 0)
                break;
        }
        numtries++;
    } while (numtries < dataLink->numTransmissions);
    unsetAlarm();
}

int llclose(int fd)
{

    if (TRANSMITTER == dataLink->status)
    {
        closeTransmitter(fd);
    }
    else if (RECEIVER == dataLink->status)
    {
        closeReceiver(fd);
    }
    if (tcsetattr(fd, TCSANOW, &oldtio) == -1)
    {
        perror("tcsetattr");
        return -1;
    }

    if (close(fd) < 0)
    {
        perror("close fd");
        return -1;
    }

    unsetDisconect();

    return 0;
}

int sendDataFrame(int fd, int Ns, char *buffer, int len)
{
    unsigned char set[dataLink->maxFrameSize];

    set[0] = FLAG;
    set[1] = A1;
    set[2] = Ns ? 0x40 : 0x00;
    set[3] = set[1] ^ set[2];

    int pos = 4;
    for (int i = 0; i < len && pos < dataLink->maxFrameSize - 2; i++)
    {
        if (buffer[i] == FLAG || buffer[i] == ESC)
        { //byte stuffing
            set[pos++] = ESC;
            set[pos++] = buffer[i] ^ STUFFING;
        }
        else
            set[pos++] = buffer[i];
    }

    unsigned char bcc2 = 0;
    for (int i = 3; i < pos; i++)
        bcc2 ^= set[i];

    if (bcc2 == FLAG || bcc2 == ESC)
    {
        set[pos++] = ESC;
        set[pos++] = bcc2 ^ STUFFING;
    }
    else
    {
        set[pos++] = bcc2;
    }

    set[pos++] = FLAG;

    return write(fd, set, pos);
}

int readDataFrame(int fd, char *buffer)
{

    unsigned char c;
    int state = START;
    unsigned char c_received;

    int i = -1;
    unsigned char xor = 0;
    unsigned char last = 0;
    int error = generateErrorChance(dataLink->fer);

    STOP = FALSE;
    simulateDelay(dataLink->T_prop);

    while (STOP == FALSE)
    {
        read(fd, &c, 1);
        switch (state)
        {
        case START:
            if (c == FLAG)
                state = FLAG_RCV;
            else {
                
            }
            break;
        case FLAG_RCV:
            xor = 0;
            last = 0;
            if (c == A1)
                state = A_RCV;
            else if (c == FLAG)
                state = FLAG_RCV;
            else
                state = START;
            break;
        case A_RCV:
            if ((c_received = c) == 0x40 || c == 0x00)
            {
                state = C_RCV;
            }
            else if (c == FLAG)
                state = FLAG_RCV;
            else if (c == DISC)
            {
                state = C_RCV;
            }
            else
                state = START;
            break;
        case C_RCV:
            if (c == FLAG)
                state = FLAG_RCV;
            else if (c == A1 ^ c_received)
            {
                state = BCC_OK;
                xor ^= c;
            }
            else
                state = START;
            break;
        case BCC_OK:
            if (c == FLAG)
            {
                if (i == -1 && c_received == DISC)
                    return 1;
                if (last == xor || (destuffEscape && (last ^ STUFFING == xor)))
                {
                    destuffEscape = FALSE;
                    unsigned int token = ((c_received ^ 0x40) << 1) | RR_ZERO;
                    if (error == 0)
                        sendControlFrame(fd, token);
                    else
                    {
                        printf(" - Random data error simulated.\n");
                        if (c_received == 0x40)
                            sendControlFrame(fd, REJ_ZERO);
                        else if (c_received == 0x00)
                            sendControlFrame(fd, REJ_ONE);
                    }

                    return 0;
                }

                unsigned int token = ((c_received) << 1) | REJ_ZERO;
                if (error == 0)
                    if (c_received == 0x40)
                        sendControlFrame(fd, REJ_ZERO);
                    else if (c_received == 0x00)
                        sendControlFrame(fd, REJ_ONE);
                    else
                    {
                        printf(" - Random data error simulated.\n");
                        if (c_received == 0x40)
                            sendControlFrame(fd, REJ_ZERO);
                        else if (c_received == 0x00)
                            sendControlFrame(fd, REJ_ONE);
                    }
                return 0;
            }
            else
            {

                if (last == ESC)
                {
                    if (destuffEscape)
                    {
                        buffer[i] = last ^ STUFFING;
                        xor ^= buffer[i];
                        last = c;
                        destuffEscape = FALSE;
                        i++;
                        continue;
                    }
                    else
                    {
                        destuffEscape = TRUE;
                        xor ^= last;
                        last = c;
                        continue;
                    }
                }

                if (i != -1)
                {
                    if (destuffEscape)
                    {
                        buffer[i] = last ^ STUFFING;
                        xor ^= last;
                        destuffEscape = FALSE;
                    }
                    else
                    {
                        buffer[i] = last;
                        xor ^= last;
                    }
                }
                last = c;
                i++;
            }
        }
    }
    sendControlFrame(fd, REJ_ZERO);
    return -1;
}

int llread(int fd, char *buffer)
{
    int numtries = 0;
    int ret;
    setAlarm();
    do
    {
        alarm(dataLink->timeout);
        ret = readDataFrame(fd, buffer);
        numtries++;
    } while ((ret != 0) && (numtries < dataLink->numTransmissions));
    unsetAlarm();

    if (numtries >= dataLink->numTransmissions && ret == -1)
    { //could not read frame
        perror("Connection Timed Out");
        exit(-1);
    }
    return ret;
}

int llwrite(int fd, char *buffer, int length)
{

    int N = nSentSuccesfull % 2 ? 0x40 : 0x00, numtries = 0, bytesWritten = 0;
    unsigned char response;
    setAlarm();
    do
    {
        bytesWritten = sendDataFrame(fd, N, buffer, length);
        alarm(dataLink->timeout);
        numtries++;
        response = readControlFrame(fd);

        if (response == RR_ONE)
        {
            if (!N)
            {
                nSentSuccesfull++;
                break;
            }
            else
            {
                nSentSuccesfull++;
                readControlFrame(fd); // when repeated there are multiples controlframes, so we are getting the response of previous sent packages, this fixes that error
                break;
            }
        }
        else if (response == RR_ZERO)
        {
            if (N)
            {
                nSentSuccesfull++;
                break;
            }
            else
            {
                nSentSuccesfull++;
                readControlFrame(fd);
                break;
            }
        }
    } while (numtries < dataLink->numTransmissions);
    unsetAlarm();

    if (numtries >= dataLink->numTransmissions && response == 255)
    { //could not write frame
        perror("Connection Timed Out");
        exit(-1);
    }

    return bytesWritten;
}

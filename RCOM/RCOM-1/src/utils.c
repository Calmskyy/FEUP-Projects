#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

long getFileSize(FILE *f)
{
    fseek(f, 0, SEEK_END); // seek to end of file
    long size = ftell(f);  // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    return size;
}

void printProgressBar(int progress, long fileSize)
{
    char *progressBar = calloc(32, sizeof(char));
    memcpy(progressBar, "Progress [                    ]", 32);
    int progressPercentage = (int)((float)progress / (float)fileSize * 100);
    if (progressPercentage > 100)
    progressPercentage = 100;
    for (int i = 0; i < progressPercentage / 5; i++)
    {
        progressBar[i + 10] = '#';
    }

    printf("\r%s %d%%", progressBar, progressPercentage);
    fflush(stdout);
}

void printUsage(char * progName) {
	printf("Usage:\t%s <Port Number> <0 (Receiver) || 1 (Sender)> <FileName (to write to/send)> <BaudRate: 0(B38400) || 1(B19200) || 2(B4800)> <DataSize> <MaxRetries> <Timeout> <Delay (in microseconds)> <RandomError (1 in RandomError chances)>\n", progName);
	printf("\tex: %s 0 0 pinguim.gif 12000 20 3 3 2000 30\n", progName);
    printf("Can also use the first 3 arguments and remaining ones will take default values\n");
    printf("\tex: %s 0 0 pinguim.gif\n", progName);
}

int generateErrorChance(unsigned int fer)
{
    if (fer == 0)
        return 0;
    static int rngInitialized = 0;
    if (rngInitialized == 0) {
        srandom(time(NULL));
        rngInitialized = 1;
    }
    int randNum = random() % fer;
    if (randNum == 0)
    return 1;
    else
    return 0;
}

void simulateDelay(unsigned int T_prop) {
    usleep(T_prop);
}

int getBaudRate(int baudRateIndex) {
    int baudrate = 0;
    switch (baudRateIndex)
    {
    case 0:
        baudrate = B600;
        break;
    case 1:
        baudrate = B1200;
        break;
    case 2:
        baudrate = B1800;
        break;
    case 3:
        baudrate = B2400;
        break;
    case 4:
        baudrate = B4800;
        break;
    case 5:
        baudrate = B9600;
        break;
    case 6:
        baudrate = B19200;
        break;
    case 7:
        baudrate = B38400;
        break;
    default:
        break;
    }
    return baudrate;
}

int printBaudRate(int baudRateIndex) {
    int baudrate = 0;
    switch (baudRateIndex)
    {
    case 0:
        baudrate = 600;
        break;
    case 1:
        baudrate = 1200;
        break;
    case 2:
        baudrate = 1800;
        break;
    case 3:
        baudrate = 2400;
        break;
    case 4:
        baudrate = 4800;
        break;
    case 5:
        baudrate = 9600;
        break;
    case 6:
        baudrate = 19200;
        break;
    case 7:
        baudrate = 38400;
        break;
    default:
        break;
    }
    return baudrate;
} 
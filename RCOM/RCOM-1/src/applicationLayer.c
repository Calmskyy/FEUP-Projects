#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataLinkLayer.c"
#include "applicationLayer.h"

#define CLOCK_PRECISION 1E9
#define DATA 1
#define START_PACKET 2
#define END_PACKET 3
#define NOISE -1
#define FILE_SIZE 0
#define FILE_NAME 1
#define MAX_FILE_NAME 32
#define DEFAULT_DELAY 0
#define DEFAULT_FER 0
#define DEFAULT_BAUDRATE 7
#define DEFAULT_DATASIZE 32
#define DEFAULT_NUM_RETRIES 5
#define DEFAULT_TIMEOUT 3

static ApplicationLayer *app;

int initApplicationLayer(int porta, int type, char *fileName, int baudRate, int dataSize, int retries, int timeout, int delay, int random)
{

    app = malloc(sizeof(ApplicationLayer));
    app->fileName = malloc(sizeof(char) * strlen(fileName));
    app->serialPort = porta;
    app->status = type;
    app->dataSize = dataSize;
    strcpy(app->fileName, fileName);

    if ((app->fileDescriptor = llopen(app->serialPort, app->status)) < 0)
    {
        perror("llopen");
        exit(-1);
    }

    if (type == TRANSMITTER)
        sendFile();
    else if (type == RECEIVER)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        int finalFileSize = receiveFile();
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        double timeElapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / CLOCK_PRECISION;
        printf("\nTime elapsed: %f s\n", timeElapsed);

        float transmissionSpeed = getBaudRate(baudRate);
        float bitsPerSecond = (float)finalFileSize / timeElapsed;
    
        printf("Bits received/second (R): %0.2f\n", bitsPerSecond);
        printf("Baudrate (C) : %d\n", printBaudRate(baudRate));
        printf("Efficiency (R/C) = %0.2f%%\n", bitsPerSecond / (float)printBaudRate(baudRate) * 100);
    }

    return llclose(app->fileDescriptor);
}

void destroyApplicationLayer()
{
    free(app->fileName);
    free(app);
}

int sendControlPacket(long fileSize, int nameLength, int type)
{
    int packetSize = 5 + sizeof(fileSize) + nameLength;
    unsigned char controlPacket[packetSize];

    int i = 0;

    controlPacket[i++] = type;
    controlPacket[i++] = FILE_SIZE;
    controlPacket[i++] = sizeof(long);
    memcpy(&controlPacket[i], &fileSize, sizeof(fileSize));

    i += sizeof(fileSize);

    controlPacket[i++] = FILE_NAME;
    controlPacket[i++] = nameLength;
    memcpy(&controlPacket[i], app->fileName, nameLength);

    return llwrite(app->fileDescriptor, controlPacket, packetSize);
}

int sendDataPacket(int sequenceNumber, unsigned char *data, int dataSize)
{
    int packetSize = 4 + dataSize;
    unsigned char dataPacket[packetSize];

    dataPacket[0] = DATA;
    dataPacket[1] = sequenceNumber % 256;
    dataPacket[2] = dataSize / 256;
    dataPacket[3] = dataSize % 256;
    memcpy(&dataPacket[4], data, dataSize);

    return llwrite(app->fileDescriptor, dataPacket, packetSize);
}

int receivePacket(unsigned char *packet, void *storedPacket)
{
    llread(app->fileDescriptor, packet);

    if (packet[0] == DATA)
    {
        return receiveDataPacket(packet, storedPacket);
    }
    else if (packet[0] == START_PACKET || packet[0] == END_PACKET)
    {
        return receiveControlPacket(packet, storedPacket);
    }
    else
    { //noise
        return NOISE;
    }
}

int receiveDataPacket(unsigned char *dataPacket, DataPacket *storedPacket)
{ //  returns type of packet -> DATA
    storedPacket->size = 256 * dataPacket[2] + dataPacket[3];
    storedPacket->sequenceNumber = dataPacket[1];
    storedPacket->data = malloc(storedPacket->size);
    memcpy(storedPacket->data, &dataPacket[4 + storedPacket->size], storedPacket->size);

    return dataPacket[0];
}

int receiveControlPacket(unsigned char *controlPacket, ControlPacket *storedPacket)
{ //  returns type of packet -> START_PACKET || END_PACKET
    storedPacket->type = controlPacket[0];
    storedPacket->fileName = malloc(controlPacket[4 + controlPacket[2]]);
    memcpy(&storedPacket->fileSize, &controlPacket[3], controlPacket[2]);
    memcpy(storedPacket->fileName, &controlPacket[5 + controlPacket[2]], controlPacket[4 + controlPacket[2]]);

    return controlPacket[0];
}

int sendFile()
{
    FILE *file = fopen(app->fileName, "r");
    long fileSize = getFileSize(file);
    int nameLength = strlen(app->fileName);

    if (sendControlPacket(fileSize, nameLength, START_PACKET) <= 0)
    {
        perror("Transmitting Control Packet");
        exit(-1);
    }

    int sequenceNumber = 0, progress = 0;
    unsigned char *fileBuffer = (unsigned char *)malloc(app->dataSize * sizeof(char));
    int size;
    while ((size = fread(fileBuffer, sizeof(char), app->dataSize, file)))
    {
        if (sendDataPacket(sequenceNumber++, fileBuffer, size) <= 0)
        {
            perror("Transmitting Data Packet\n");
            exit(-1);
        }
        progress += app->dataSize;
        printProgressBar(progress, fileSize);
    }

    if (sendControlPacket(fileSize, nameLength, END_PACKET) <= 0)
    {
        perror("Transmitting Control Packet\n");
        exit(-1);
    }

    printf("\nFile sent\n");

    free(fileBuffer);

    if (fclose(file))
    {
        perror("Error while closing file\n");
        return -1;
    }
}

int receiveFile()
{
    ControlPacket storedControlPacket;
    int packetSize = 4 + app->dataSize;
    unsigned char controlPacket[packetSize];
    if (receivePacket(controlPacket, &storedControlPacket) != START_PACKET)
    {
        perror("Receiving Control\n");
        exit(-1);
    }
    long fileSize = storedControlPacket.fileSize;

    FILE *receivedFile = fopen(app->fileName, "wb");
    unsigned char packet[packetSize];
    DataPacket storedDataPacket;
    int lastPacket = 0, progress = 0, sequenceNumber = 0, noiseInput = 0, duplicatePackets = 0;
    int lastStoredDataPacket = -1;
    while (((lastPacket = receivePacket(packet, &storedDataPacket)) == DATA) || (lastPacket == NOISE))
    {   
        if (lastPacket == NOISE)
        { //protection against noise
            noiseInput++;
            continue;
        }
        if (lastStoredDataPacket == storedDataPacket.sequenceNumber)
        { //duplicate packet -> ignore packet
            duplicatePackets++;
            fseek(receivedFile, -app->dataSize, SEEK_CUR);
            progress -= app->dataSize;
            sequenceNumber--;
            //continue;
        }
        lastStoredDataPacket = storedDataPacket.sequenceNumber;
        progress += app->dataSize;
        for (int i = 0; i < packet[2] * 256 + packet[3]; i++)
            fputc(packet[i + 4], receivedFile);

        sequenceNumber = (sequenceNumber + 1) % 256;
        printProgressBar(progress, fileSize);
    }
    printf("\nDuplicate Packets: %d", duplicatePackets);
    int finalFileSize = getFileSize(receivedFile) * 8;
    fclose(receivedFile);
    if (lastPacket != END_PACKET)
    {
        exit(-1);
    }

    return finalFileSize;
}

int main(int argc, char **argv)
{

    int port, type, delay, random, baudRate, dataSize, maxTries, timeout;
    char *fileName;
    if (argc < 4 || (argc > 4 && argc < 10) || argc > 10)
    {
        printUsage(argv[0]);
        exit(1);
    }
    if ((argc == 4) &&
        ((strcmp("0", argv[2]) == 0) ||
         (strcmp("1", argv[2]) == 0)))
    {
        port = atoi(argv[1]);
        type = atoi(argv[2]);
        fileName = argv[3];
        baudRate = DEFAULT_BAUDRATE;
        dataSize = DEFAULT_DATASIZE;
        maxTries = DEFAULT_NUM_RETRIES;
        timeout = DEFAULT_TIMEOUT;
        delay = DEFAULT_DELAY;
        random = DEFAULT_FER;
    }
    else {
        port = atoi(argv[1]);
        type = atoi(argv[2]);
        fileName = argv[3];
        baudRate = atoi(argv[4]);
        dataSize = atoi(argv[5]);
        maxTries = atoi(argv[6]);
        timeout = atoi(argv[7]);
        delay = atoi(argv[8]);
        random = atoi(argv[9]);
    }
    
    //Estatistics 

    //variable frame size
    // unsigned int sizes[8] = {2, 8, 32, 64, 256, 1024, 2048, 4096};
    // for (int i = 0; i < 8; i++) {
    //     printf("data size = %d\n", sizes[i]);
    //     initDataLinkLayer(port, type, baudRate, sizes[i], maxTries, timeout, delay, random);
    //     initApplicationLayer(port, type, fileName, baudRate, sizes[i], maxTries, timeout, delay, random);
    //     destroyApplicationLayer();
    //     printf("\n\n");
    // }

    //variable baudrate
    //  unsigned int baudRates[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    //  for (int i = 0; i < 8; i++) {
    //      printf("baudRate test = %d\n", baudRates[i]);
    //      initDataLinkLayer(port, type, baudRates[i], dataSize, maxTries, timeout, delay, random);
    //      initApplicationLayer(port, type, fileName, baudRates[i], dataSize, maxTries, timeout, delay, random);
    //      destroyApplicationLayer();
    //      printf("\n\n");
    //  }

    //variable frame error ratio
    // unsigned int FER[5] = {100, 20, 10, 5, 2};
    // for (int i = 0; i < 5; i++) {
    //      printf("FER = %d\n", FER[i]);
    //      initDataLinkLayer(port, type, baudRate, dataSize, maxTries, timeout, delay, FER[i]);
    //      initApplicationLayer(port, type, fileName, baudRate, dataSize, maxTries, timeout, delay, FER[i]);
    //      destroyApplicationLayer();
    //      printf("\n\n");
    //  }

    //variable propagation time
    // unsigned int delays[6] = {15000, 30000, 50000, 100000, 200000, 300000};
    //  for (int i = 0; i < 6; i++) {
    //       printf("delay = %d\n", delays[i]);
    //       initDataLinkLayer(port, type, baudRate, dataSize, maxTries, timeout, delays[i], random);
    //       initApplicationLayer(port, type, fileName, baudRate, dataSize, maxTries, timeout, delays[i], random);
    //       destroyApplicationLayer();
    //       printf("\n\n");
    //   }

    
    initDataLinkLayer(port, type, baudRate, dataSize, maxTries, timeout, delay, random);
    initApplicationLayer(port, type, fileName, baudRate, dataSize, maxTries, timeout, delay, random);
    destroyApplicationLayer();
    
    exit(0);
}
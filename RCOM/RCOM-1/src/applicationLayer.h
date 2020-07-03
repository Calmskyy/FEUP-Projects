#ifndef _APPLICATIONLAYER_H_
#define _APPLICATIONLAYER_H_

typedef struct {
    int fileDescriptor; /*File Descriptor correspondent to the serial port*/
    int serialPort; /*Number of the serial port being used*/
    int status; /*TRANSMITTER | RECEIVER*/
    int dataSize; /*Data bytes per data packet*/
    char * fileName; /*File to be transmitted*/
} ApplicationLayer;

typedef struct {
    int type; /* START_PACKET | END_PACKET */
    char  * fileName; /* Name of the file to be transmitted */
    long fileSize; /* Size of the file to be transmitted */
} ControlPacket;

typedef struct {
    unsigned int sequenceNumber; /* Sequence number of the data packet */
    unsigned int size; /* Size of the data on the packet */
    char * data; /* Data being transported on the packet */
} DataPacket;

/**
 * @brief Initializes the application layer and its components
 * 
 * @param porta Serial port Number
 * @param type Connection Type
 * @param fileName File to be transmitted
 * @param baudRate Transmission speed
 * @param dataSize Bytes to be sent as data in each data packet
 * @param retries Number of retransmission attempts should an error occur
 * @param timeout Number of seconds before a timeout is declared
 * @param delay Simulated delay between receiving packets
 * @param random Simulated chance to generate a random processing error
 * @return int 0 on success, less than 0 otherwise
 */
int initApplicationLayer(int porta, int type, char * fileName, int baudRate, int dataSize, int retries, int timeout, int delay, int random);

/**
 * @brief Frees the space allocated in the application layer
 */
void destroyApplicationLayer();

/**
 * @brief Sends a Control Packet
 * 
 * @param fileSize Size of the file to be transmitted
 * @param nameLength Length of the name of the file
 * @param type  START_PACKET | END_PACKET 
 * @return int 0 on success, less than 0 otherwise
 */
int sendControlPacket(long fileSize, int nameLength, int type);

/**
 * @brief Sends a Data Packet
 * 
 * @param sequenceNumber Sequence Number of the Data packet
 * @param data Data to be transported
 * @param dataSize Size of the data
 * @return int 0 on success, less than 0 otherwise
 */
int sendDataPacket(int sequenceNumber, unsigned char * data, int dataSize);

/**
 * @brief Reads and stores a Data packet
 * 
 * @param dataPacket Data packet to be read
 * @param storedPacket Stores the Data packet
 * @return int type of data packet read
 */
int receiveDataPacket(unsigned char * dataPacket, DataPacket * storedPacket);

/**
 * @brief Reads and stores a Control packet
 * 
 * @param controlPacket Control packet to be read 
 * @param storedPacket Stores the Control packet
 * @return int type of data packet read
 */
int receiveControlPacket(unsigned char * controlPacket, ControlPacket * storedPacket);

/**
 * @brief Calls the functions that receive packets, according to its type
 * 
 * @param packet Packet to be read
 * @param storedPacket Stores the packet
 * @return int type of data packet read
 */
int receivePacket(unsigned char * packet, void * storedPacket);

/**
 * @brief Sends a file, calling all the necessary functions to write it
 * 
 * @return int 0 on success, less than 0 otherwise
 */
int sendFile();

/**
 * @brief Receives a file, calling all the necessary functions to read it
 * 
 * @return int Number of bits written, used for the efficiency calculation
 */
int receiveFile();

#endif // _APPLICATIONLAYER_H_
#ifndef _DATALINKLAYER_H_
#define _DATALINKLAYER_H_

typedef struct {
    char port[20]; /*Dispositivo /dev/ttySx, x = 0, 1*/
    int baudRate; /*Velocidade de transmissão*/
    unsigned int sequenceNumber; /*Número de sequência da trama: 0, 1*/
    unsigned int timeout; /*Valor do temporizador*/
    unsigned int numTransmissions; /*Número de tentativas em caso de falha*/
    int status; /*TRANSMITTER | RECEIVER*/
    int T_prop; /*Simulated delay upon recieving packets*/
    int fer; /*Simulated random error chance upon recieving packets*/
    int maxFrameSize;
} DataLinkLayer;

/**
 * @brief Makes so that the a packet is retransmitted
 * 
 * @param signal 
 */
void alarmHandler(int signal);

/**
 * @brief Set the Alarm object
 * 
 */
void setAlarm();

/**
 * @brief Uninstalls the alarm
 * 
 */
void unsetAlarm();

/**
 * @brief Sends a Control frame
 * 
 * @param fd File descriptor where to write the frame
 * @param controlField Control field of the frame
 * @return int 0 on sucess, less than 0 otherwise
 */
int sendControlFrame(int fd, char controlField);

/**
 * @brief Reads a Control frame and checks its control field
 * 
 * @param fd File descriptor from where to read the frame
 * @param controlField Control field that is expected
 * @return int 0 on sucess, less than 0 otherwise
 */
int checkControlFrame(int fd, char controlField);

/**
 * @brief Reads a Control frame
 * 
 * @param fd File descriptor from where to read the frame
 * @return int Control field read on sucess, less than 0 otherwise
 */
int readControlFrame(int fd);

/**
 * @brief Sends a Data frame
 * 
 * @param fd File descriptor where to write the frame
 * @param Ns Control field of the frame
 * @param buffer Buffer containing the data to be sent
 * @param len Length of the buffer
 * @return int 0 on sucess, less than 0 otherwise
 */
int sendDataFrame(int fd, int Ns, char *buffer, int len);

/**
 * @brief Reads a Data frame
 * 
 * @param fd File descriptor from where to read the frame
 * @param buffer Buffer containing the data to be read
 * @return int 0 on sucess, less than 0 otherwise
 */
int readDataFrame(int fd, char *buffer);

/**
 * @brief Opens serial port and sets its attributes accordingly
 * 
 * @return int File descriptor corresponding to the port
 */
int openPort();

/**
 * @brief Opens serial port and establishes the connection
 * 
 * @param porta Number of the serial port
 * @param type Connection type
 * @return int File descriptor corresponding to the port
 */
int llopen(int porta, int type);

/**
 * @brief Communication that allows the transmitter to stop
 * 
 * @param fd File descriptor corresponding to the port
 */
void closeTransmitter(int fd);

/**
 * @brief Communication that allows the receiver to stop
 * 
 * @param fd File descriptor corresponding to the port
 */
void closeReceiver(int fd);

/**
 * @brief Opens serial port and terminates the connection
 * 
 * @param fd File descriptor corresponding to the port
 * @return int 0 on success, less than 0 otherwise
 */
int llclose(int fd);

/**
 * @brief Reads a Data frane
 * 
 * @param fd File descriptor from where to read the frame
 * @param buffer Buffer containing the data to be read
 * @return int int 0 on sucess, less than 0 otherwise
 */
int llread(int fd, char *buffer);

/**
 * @brief Writes the data frame, trying at most MAX_NUM_TRIES
 * 
 * @param fd File descriptor where to write the frame
 * @param buffer Buffer containing the data to be written
 * @param length Length of the data
 * @return int bytes written on success, -1 otherwise
 */
int llwrite(int fd, char *buffer, int length);

#endif // _DATALINKLAYER_H_
#ifndef __CLIENTFTP_H
#define __CLIENTFTP_H

#include <string.h>
#include <ctype.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <regex.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEBUG 0

#define SERVER_READY "220"
#define SERVICE_CLOSING "221"
#define TRANSFER_COMPLETE "226"
#define REQUIRED_PASSWORD "331"
#define SUCCESS_LOGIN "230"
#define FINISHED "150"
#define TRANSFER_STARTING "125"
#define PASSIVE_MODE "227"
#define DIRECTORY_OK "250"
#define SET_TYPE "200"
#define PASSIVE_MODE_COMMAND "pasv"
#define QUIT_COMMAND "quit"
#define READ_RESPONSE_CODE 0
#define MULTIPLE_LINE_RESPONSE 1
#define FINISH_READING 2
#define READING_ERROR 3

typedef struct ftp_t
{
	int fdControl;
	int fdData;
} FTP;

/**
 * @brief Establishes a connection to the server
 * 
 * @param ip IP of the server to connect to
 * @param port Port used on the connection
 * @return int File descriptor of the server socket
 */
int connectSocket(const char *ip, int port);

/**
 * @brief Closes the connection to the server
 * 
 * @param sockfd File descriptor of the server socket
 * @return int 0 on success, 1 otherwise
 */
int closeSocket(int sockfd);

/**
 * @brief Reads a response code sent by the server
 * 
 * @param sockfd File descriptor of the server socket
 * @param response Response code read
 * @return int 0 on success, 1 otherwise
 */
int getResponse(int sockfd, char *response);

/**
 * @brief Sends a command to the server
 * 
 * @param sockfd File descriptor of the server socket
 * @param command Command to be sent
 */
void sendCommand(int sockfd, char command[]);

/**
 * @brief Sends a command to the server, and reads the response sent afterwards
 * 
 * @param sockfd File descriptor of the server socket
 * @param command Command to be sent
 * @param response Response code read
 * @return int 0 on success, 1 otherwise
 */
int sendCommandAndGetResponse(int sockfd, char command[], char *response);

/**
 * @brief Reads the server port in the response after pasv is sent
 * 
 * @param socketfd File descriptor of the server socket
 * @param port Port read from the response
 * @return int 0 on success, 1 otherwise
 */
int getServerPortFromResponse(int socketfd, int *port);

/**
 * @brief Sends a login request to the server
 * 
 * @param sockfd File descriptor of the server socket
 * @param username Username to use on the login attempt
 * @param password Password to use on the login attempt
 * @return int 0 on success, 1 otherwise
 */
int loginFTP(int sockfd, char *username, char *password);

/**
 * @brief Checks if the server is ready to take commands
 * 
 * @param sockfd File descriptor of the server socket
 * @return int 0 on success, 1 otherwise
 */
int checkServerAvailability(int sockfd);

/**
 * @brief Changes the FTP mode
 * 
 * @param sockfd File descriptor of the server socket
 * @param mode Command used to change the mode
 * @param dataPort Port read from the response
 * @return int 0 on success, 1 otherwise
 */
int setFTPMode(int sockfd, char *mode, int *dataPort);

/**
 * @brief Downloads a file from the server
 * 
 * @param sockfd File descriptor of the server socket
 * @param filePath Path to the file on the server
 * @param fileName Name of the file on the server
 * @param socketData File descriptor of the data socket
 * @return int 0 on success, 1 otherwise
 */
int downloadFile(int sockfd, char *filePath, char *fileName, int socketData);

/**
 * @brief Copies the server file to a file created locally
 * 
 * @param fd File descriptor of the data socket
 * @param filename Name of the created file
 */
void createFile(int fd, char* filename);

/**
 * @brief Destroys the socket used on the connection
 * 
 * @param fd File descriptor of the data socket
 */
void destroySocket(int fd);

#endif /* __CLIENTFTP_H */

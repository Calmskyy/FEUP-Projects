/*      (C)2000 FEUP  */

#include "clientFTP.h"
#include "utils.h"

#define SERVER_PORT 6000
#define SERVER_ADDR "192.168.28.96"

int connectSocket(const char *ip, int port)
{

	int sockfd;
	struct sockaddr_in server_addr;

	/*server address handling*/
	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip); /*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port);			 /*server TCP port must be network byte ordered */

	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(0);
	}
	/*connect to the server*/
	if (connect(sockfd,
				(struct sockaddr *)&server_addr,
				sizeof(server_addr)) < 0)
	{
		perror("connect()");
		exit(0);
	}

	return sockfd;
}

int getResponse(int sockfd, char *response)
{
	char c;
	int i = 0;
	int state = READ_RESPONSE_CODE;

	while (state != READING_ERROR)
	{
		recv(sockfd, &c, 1, 0);
		printf("%c", c);
		switch (state)
		{
		case READ_RESPONSE_CODE:
			if (isdigit(c))
			{
				if (i >= 3)
				{
					printf("Response code wasn't read correctly.\n");
					state = READING_ERROR;
				}
				response[i] = c;
				i++;
				break;
			}
			if (i != 3)
			{
				printf("Response code wasn't read correctly.\n");
				state = READING_ERROR;
			}
			else
			{
				if (c == '-')
				{
					i = 0;
					state = MULTIPLE_LINE_RESPONSE;
				}
				else if (c == ' ')
					state = FINISH_READING;
			}
			break;
		case MULTIPLE_LINE_RESPONSE:
			if (c == response[i])
			{
				i++;
				break;
			}
			if (i == 3)
			{
				if (c == '-')
					i = 0;
				else if (c == ' ')
					state = FINISH_READING;
			}
			break;
		case FINISH_READING:
			if (c == '\n')
				return 0;
			break;
		}
	}
	printf("\n");
	return 1; // error occurred
}

int sendCommandAndGetResponse(int sockfd, char command[], char *response)
{
	sendCommand(sockfd, command);
	return getResponse(sockfd, response);
}

void sendCommand(int sockfd, char command[])
{
	send(sockfd, command, strlen(command), 0);
    printf("> %s\n", command);
	send(sockfd, "\r\n", 2, 0);
}

int checkServerAvailability(int sockfd) {

	char response[4];
	getResponse(sockfd, response);
    if (strcmp(response, SERVER_READY) == 0)
        return 0;
    else
        return 1;
}

int loginFTP(int sockfd, char *username, char *password)
{
    char response[4];
	char usercmd[strlen(username) + 5];
	sprintf(usercmd, "user %s", username);
	if (sendCommandAndGetResponse(sockfd, usercmd, response) != 0)
		return 1;
	if (strcmp(response, REQUIRED_PASSWORD) == 0)
	{
		char passcmd[strlen(password) + 5];
		sprintf(passcmd, "pass %s", password);
		if (sendCommandAndGetResponse(sockfd, passcmd, response) != 0)
			return 1;
		if (strcmp(response, SUCCESS_LOGIN) == 0)
			return 0;
	}
	return 1;
}

int setFTPMode(int sockfd, char *mode, int *port)
{
	sendCommand(sockfd, mode);

	if (getServerPortFromResponse(sockfd, port))
		return 1;

	return 0;
}

int downloadFile(int sockfd, char *filePath, char *fileName, int socketData){
	char response[4];

	char *file = malloc(strlen(filePath) + strlen(fileName) + 1);
	strcpy(file, filePath);
    strcat(file, fileName);
	char cmd[strlen(file) + 5];
	sprintf(cmd, "retr %s", file);

	if (sendCommandAndGetResponse(sockfd, cmd, response) != 0)
		return 1;
	if (strcmp(response, FINISHED) && strcmp(response, TRANSFER_STARTING)){
		return 1;
	}

	createFile(socketData, fileName);

	if (getResponse(sockfd, response) != 0)
		return 1;

	if (strcmp(response, TRANSFER_COMPLETE))
		return 1;

	return 0;
}

void createFile(int sockfd, char* filename)
{
    FILE *file = fopen((char *)filename, "wb+");

	int BUF_SIZE = 512;
    int dots = 0;

    char bufSocket[BUF_SIZE];
	int bytes;
	while ((bytes = read(sockfd, bufSocket, BUF_SIZE))>0) {
		bytes = fwrite(bufSocket, bytes, 1, file);
        printDownloadProgress(&dots);
    }

    fclose(file);

    printf("\nFinished downloading file\n");
}

void destroySocket(int sockfd){
	close(sockfd);
}

int closeSocket(int sockfd){
	char response[4];

	if (sendCommandAndGetResponse(sockfd, QUIT_COMMAND, response) != 0)
		return 1;
	if (strcmp(response, SERVICE_CLOSING)){
		return 1;
	}
	return 0;
}

int getServerPortFromResponse(int socketfd, int *port)
{
    int index = 0;

	char message[256];
	memset(message, 0, 256);

	int a,b,ca,d;
	int pa,pb;

	char c;

	while (read(socketfd, &c, 1)){
		message[index++] = c;
		if (c == '\n'){
			message[index] = 0;
			break;
		}
	}

	char res[4];
	memcpy(res, message, 3);
	res[3] = 0;

	if (strcmp(res, PASSIVE_MODE))
		return 1;

	char *find = strrchr(message, '(');

	if (find == NULL)
		return 1;

	sscanf(find, "(%d,%d,%d,%d,%d,%d)", &a, &b, &ca, &d, &pa, &pb);
	// sprintf(ipaddr, "%d.%d.%d.%d", a, b, c, d);
	*port = pa * 256 + pb;
	return 0;
}

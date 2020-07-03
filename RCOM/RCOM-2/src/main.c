#include "URLParser.h"
#include "clientFTP.h"

#define BUFFER_SIZE 1024

void printUsage(char ** argv) {
	printf(
    "\nUsage: %s ftp://[<user>:<password>@]<host>/<url-path>\n",
		argv[0]);
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printUsage(argv);
        exit(1);
    }

    URL * url = constructURL();
    
    if (parseURL(url, argv[1])) {
        perror("Unable to Parse URL");
        exit(1);
    }

    setIp(url);
    printURL(url);

    FTP * ftp = (FTP *) malloc(sizeof(FTP));

    //Opens socket to enable FTP configurantion
    if((ftp->fdControl = connectSocket(url->ip, url->port)) == 0) {
		perror("Failed to open control Connection");
        exit(1);
    }
    printf("Control Socket = %d\n", ftp->fdControl);

    if (checkServerAvailability(ftp->fdControl) != 0) {
		perror("Server is not ready");
        exit(1);
    }

    if (loginFTP(ftp->fdControl, url->username, url->password) != 0) {
        perror("Failed to login");
        exit(1);
    }

    int portData;

    if (setFTPMode(ftp->fdControl, PASSIVE_MODE_COMMAND, &portData) != 0) {
        perror("Failed to set FTP mode");
        exit(1);
    }

    printf("Port Data: %d\n", portData);

    //Opens socket to enable data transmission
    if((ftp->fdData = connectSocket(url->ip, portData)) == 0) {
		perror("Failed to open data Connection");
        exit(1);
    }
    printf("Data Socket = %d\n", ftp->fdData);
    
    if (downloadFile(ftp->fdControl, url->path, url->filename, ftp->fdData) != 0){
        perror("Failed to download file");
        exit(1);
    }

    if (closeSocket(ftp->fdControl)){
        perror("Failed to close socket");
        exit(1);
    }

    destroySocket(ftp->fdControl);
    destroySocket(ftp->fdData);
    destructURL(url);
    free(ftp);

    printf("Program Terminated with Success!\n");
    return 0;
}

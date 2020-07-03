#include "constants.h"
#include <stdio.h>
#include <string.h>

static const char SALT_BASE[] = "ABCDEF0123456789";

char *getSalt(){
    char *salt = (char *) malloc(sizeof(char) * (SALT_LEN + 1));

    for(int i = 0; i  < SALT_LEN; i++){
        int n = rand() % strlen(SALT_BASE + 1);
        salt[i] = SALT_BASE[n];
    }
    salt[strlen(salt)] = '\0';

    return salt;
}

char *getHash(char *password, char *salt){
    FILE *fp;
    char concat[MAX_PASSWORD_LEN];
    strcpy(concat,password);
    strcat(concat, salt);
    char cmd[256];
    char *hash  = (char *) malloc(sizeof(char) * (HASH_LEN + 1));

    sprintf(cmd, "echo -n %s | sha256sum",password); 

    fp = popen(cmd,"r");

    if(fgets(hash, HASH_LEN + 1, fp) != NULL){
        pclose(fp);
        return hash;
    }

    return NULL;
}

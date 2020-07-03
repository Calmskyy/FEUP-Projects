#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "utils.h"

#define MAX_ERROR_MSG 0x1000

/*
 * Compile the regular expression described by "regex_text" into "r".
 */
int compile_regex(regex_t *r, const char *regex_text)
{
  int status = regcomp(r, regex_text, REG_EXTENDED | REG_NEWLINE);
  if (status != 0)
  {
    char error_message[MAX_ERROR_MSG];
    regerror(status, r, error_message, MAX_ERROR_MSG);
    printf("Regex error compiling '%s': %s\n",
           regex_text, error_message);
    return 1;
  }
  return 0;
}

char *getIp(char *domain)
{
  struct hostent *h;
  if ((h = gethostbyname(domain)) == NULL)
  {
    herror("gethostbyname");
    exit(1);
  }

  return inet_ntoa(*((struct in_addr *)h->h_addr));
}

void printDownloadProgress(int *dots)
{
  (*dots)++;

  switch (*dots)
  {
  case 1:
    printf("\r                  ");
    printf("\rDownloading.");
    break;
  case 2:
    printf(".");
    break;
  case 3:
    printf(".");
    *dots = 0;
    break;
  }

  fflush(stdout);
}

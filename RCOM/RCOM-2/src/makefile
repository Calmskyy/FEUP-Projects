COMPILER_TYPE = gnu
CC = gcc

PROG = download
SRCS = main.c utils.c URLParser.c clientFTP.c

CFLAGS= -Wall -g

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(PROG)
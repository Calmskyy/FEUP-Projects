all: server user

user: user.c
	gcc -o user user.c -Wall -Wextra -Werror

server: server.c 
	gcc -pthread -o server server.c -Wall -Wextra -Werror

clean:
	rm -rf *.o *.txt *~ user server

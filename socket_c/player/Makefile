EXEC=server
CC=gcc
CFLAGS=-Wall
 
$(EXEC): server.o
        $(CC) -o server server.o -L../lib -lserverfuncs -lpthread
 
%.o: %.c
        $(CC) -c -I../include  $< -o $@ -lpthread
 
clean:
        rm server.o server
CC=gcc
LIB=libserverfuncs.so.1.0
OBJS=thread.o addclient.o removeclient.o getmax.o tcp_listen.o
CFLAGS=-Wall
POINTER=libserverfuncs.so libserverfuncs.so.1
 
$(LIB): $(OBJS)
        $(CC) -fPIC -shared -Wl,-soname=libserverfuncs.so.1 $(OBJS) -o $@ -lc
        ln -s libserverfuncs.so.1.0 libserverfuncs.so
        ln -s libserverfuncs.so.1.0 libserverfuncs.so.1
 
%.o: %.c
        $(CC) -fPIC -c $(CFLAGS) -I../include  $< -o $@
 
clean:
        rm -f $(OBJS) $(LIB) $(POINTER)
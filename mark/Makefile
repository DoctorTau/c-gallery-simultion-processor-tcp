CC = gcc
CFLAGS = -Wall -Wextra -pedantic -lrt -pthread -fsanitize=address
SERVER_SRC = server.c
CLIENT_SRC = client.c
COMMON_HEADER = common.h
SERVER_EXE = server
CLIENT_EXE = client

all: server client

server: $(SERVER_SRC) $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $(SERVER_EXE) $(SERVER_SRC)

client: $(CLIENT_SRC) $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $(CLIENT_EXE) $(CLIENT_SRC)

clean:
	rm -f $(SERVER_EXE) $(CLIENT_EXE)

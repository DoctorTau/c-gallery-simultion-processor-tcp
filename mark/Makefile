CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lrt -lpthread

SRC_DIR = src
BUILD_DIR = build

SERVER_SRC = $(wildcard $(SRC_DIR)/server*.c $(SRC_DIR)/queue*.c)
CLIENT_SRC = $(wildcard $(SRC_DIR)/client*.c)

SERVER_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(CLIENT_SRC))

all: server client

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)/* server client

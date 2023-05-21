CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2 -g -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = -lm -lrt -fsanitize=address -static-libasan
BUILD_DIR = build
SRC_DIR = src

SERVER_SRCS = $(SRC_DIR)/server.c $(SRC_DIR)/queue.c
CLIENT_SRCS = $(SRC_DIR)/client.c
SERVER_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SERVER_SRCS))
CLIENT_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(CLIENT_SRCS))

.PHONY: all clean

all: server client

server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

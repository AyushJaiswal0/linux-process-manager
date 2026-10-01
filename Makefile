CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = process_manager

SRC = src/main.c src/process.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
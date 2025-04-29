CC = gcc
CFLAGS = -Wall -g
SRC = $(wildcard src/*.c)
TARGET = data

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
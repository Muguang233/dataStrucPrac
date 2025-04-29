# 变量
CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c
TARGET = data

# 规则
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# 清理命令
clean:
	rm -f $(TARGET)
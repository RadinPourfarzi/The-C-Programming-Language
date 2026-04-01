CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	del $(OBJ) $(TARGET)

debug: CFLAGS += -g
debug: $(TARGET)

run: $(TARGET)
	./$(TARGET)

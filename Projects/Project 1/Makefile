CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c89
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
	./$(TARGET) -n Verse File1.txt

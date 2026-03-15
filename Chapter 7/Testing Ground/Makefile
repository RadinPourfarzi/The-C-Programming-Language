CC = gcc
CFLAGS = -Wall -Wextra -std=c11

PROGRAMS = main pipe
#COMMON = util.o io.o

all: $(PROGRAMS:%=%.exe)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.exe: main.o $(COMMON)
	$(CC) $(CFLAGS) $^ -o $@

pipe.exe: pipe.o $(COMMON)
	$(CC) $(CFLAGS) $^ -o $@

run: all
	.\main.exe

clean:
	del /Q *.o *.exe 2>nul

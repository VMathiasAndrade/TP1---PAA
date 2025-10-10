CC=gcc
CFLAGS=-Wall -Wextra -g
SRC=$(wildcard *.c) $(wildcard Jogo/*.c)
OBJ=$(SRC:.c=.o)
TARGET=app.exe

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
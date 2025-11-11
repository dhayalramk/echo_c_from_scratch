# Makefile for echo_c_from_scratch

CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic
TARGET = myecho
SRC = myecho.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "Running tests..."
	@bash test.sh

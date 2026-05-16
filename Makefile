# Variables
CC = gcc
CFLAGS = -Wall -Isrc/lexer -Isrc
SRC_DIR = src
TEST_DIR = tests

# Source files
SRCS = $(wildcard $(SRC_DIR)/lexer/*.c)
MAIN = $(SRC_DIR)/main.c
TESTS = $(TEST_DIR)/main.c

# Output
BIN = doblock

.PHONY: all clean test

# Default target: build the main application
all: $(BIN)

# Build the main app
$(BIN): $(MAIN) $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# Build and run tests (overwrites the app binary)
test: $(TESTS) $(SRCS)
	$(CC) $(CFLAGS) $^ -o $(BIN)
	./$(BIN)

# Cleanup
clean:
	rm -f $(BIN)

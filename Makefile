# Variables
CC = gcc
CFLAGS = -Wall -Isrc
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# Source files (excluding main for the test runner)
SRCS = $(SRC_DIR)/utils.c
MAIN = $(SRC_DIR)/main.c
TESTS = $(TEST_DIR)/test_utils.c

# Targets
APP_BIN = $(BIN_DIR)/app
TEST_BIN = $(BIN_DIR)/test_runner

.PHONY: all clean test

# Default target: build the main application
all: $(BIN_DIR) $(APP_BIN)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the main app
$(APP_BIN): $(MAIN) $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# Build and run tests
test: $(BIN_DIR) $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TESTS) $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# Cleanup generated files
clean:
	rm -rf $(BIN_DIR)

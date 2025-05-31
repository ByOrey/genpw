TARGET = bin/release/genpw
TEST_TARGET = bin/test/genpw_test

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc -Itest
TEST_CFLAGS = $(CFLAGS) -DCTEST_MAIN

SRC_DIR = src
OBJ_DIR = obj
TEST_OBJ_DIR = $(OBJ_DIR)/test
BIN_DIR = bin/release
TEST_BIN_DIR = bin/test

# Основная программа
MAIN_SOURCES = $(SRC_DIR)/genpw/main.c $(SRC_DIR)/libgenpw/genpw.c
MAIN_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAIN_SOURCES))

# Тестовая программа
TEST_SOURCES = test/test.c $(SRC_DIR)/libgenpw/genpw.c
TEST_OBJECTS = $(patsubst test/%.c,$(TEST_OBJ_DIR)/%.o,\
              $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SOURCES)))

all: $(TARGET)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

$(TARGET): $(MAIN_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(MAIN_OBJECTS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(TEST_OBJECTS) -o $(TEST_TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: test/%.c
	@mkdir -p $(@D)
	$(CC) $(TEST_CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN_DIR)

.PHONY: all clean test
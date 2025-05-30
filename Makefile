TARGET = bin/release/genpw

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin/release

SOURCES = $(SRC_DIR)/genpw/main.c $(SRC_DIR)/libgenpw/genpw.c
OBJECTS = $(OBJ_DIR)/genpw/main.o $(OBJ_DIR)/libgenpw/genpw.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/genpw/main.o: $(SRC_DIR)/genpw/main.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)/genpw
	$(CC) $(CFLAGS) -c $(SRC_DIR)/genpw/main.c -o $(OBJ_DIR)/genpw/main.o

$(OBJ_DIR)/libgenpw/genpw.o: $(SRC_DIR)/libgenpw/genpw.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)/libgenpw
	$(CC) $(CFLAGS) -c $(SRC_DIR)/libgenpw/genpw.c -o $(OBJ_DIR)/libgenpw/genpw.o

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN_DIR)

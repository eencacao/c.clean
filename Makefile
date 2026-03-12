CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -g -Isrc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET  = $(BIN_DIR)/todo_api

SOURCES = $(shell find $(SRC_DIR) -name "*.c")
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

all: dirs $(TARGET)

dirs:
	mkdir -p $(BIN_DIR)
	@find $(SRC_DIR) -type d | while read d; do \
	    mkdir -p $(OBJ_DIR)/$${d#$(SRC_DIR)/}; done

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

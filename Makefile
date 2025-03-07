CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = $(BIN_DIR)/user_management

.NOTPARALLEL: directories $(TARGET) clean

all: directories $(TARGET)

directories:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)
	mkdir -p $(shell find $(SRC_DIR) -type d | sed "s|^$(SRC_DIR)|$(OBJ_DIR)|")

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Ensure the obj subdirectory exists
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

debug: CFLAGS += -DDEBUG -g
debug: clean all
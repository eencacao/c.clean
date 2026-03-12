CC       = gcc
CFLAGS   = -Wall -Wextra -Wpedantic -g -Isrc
SRC_DIR  = src
OBJ_DIR  = obj
BIN_DIR  = bin
TARGET   = $(BIN_DIR)/todo_api
TEST_BIN = $(BIN_DIR)/unit_tests

SOURCES  = $(shell find $(SRC_DIR) -name "*.c")
OBJECTS  = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

TEST_SRC = tests/unit_tests.c tests/unit_main.c
TEST_OBJ = $(patsubst tests/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_SRC))
LIB_OBJ  = $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))

all: dirs $(TARGET)

test: dirs $(TEST_BIN)
	./$(TEST_BIN)

functional-test: all
	bash tests/api_test.sh

dirs:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)/tests
	@find $(SRC_DIR) -type d | while read d; do \
	    mkdir -p $(OBJ_DIR)/$${d#$(SRC_DIR)/}; done

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_BIN): $(LIB_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

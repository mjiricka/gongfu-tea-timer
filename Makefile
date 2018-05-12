TARGET := bin/gongfu
FLAGS := -g -Wall
CC := g++
SRC_DIR := src
BUILD_DIR := bin
SRC_EXT := cpp
LIBS := -lao

SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT),$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY := clean

# TODO: clean & build helpers

$(TARGET): $(OBJECTS)
	$(CC) $(LIBS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	rm -rf $(BUILD_DIR)


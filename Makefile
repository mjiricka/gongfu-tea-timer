TARGET := bin/gongfu
FLAGS := -g -Wall -O1
CC := g++
SRC_DIR := src
BUILD_DIR := bin
SRC_EXT := cpp
LIBS := -lao
INCLUDES := -I modules/argh

SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT),$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY := clean

$(TARGET): $(OBJECTS)
	$(CC) $(LIBS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)


# ==================================================================
# RULES FOR `helpers` management.
# ==================================================================

HELPER_DIR := helpers

cleanall: clean
	rm -r $(shell find $(HELPER_DIR) -executable -type f)

buildall: $(TARGET) $(shell find $(HELPER_DIR) -name Makefile)

$(HELPER_DIR)/%/Makefile: FORCE
	@cd $(HELPER_DIR)/$*; make

# THIS TARGET WILL MAKE THE PREVIOUS ONE ALWAYS RUN, EVEN WITHOUT .PHONY.
FORCE:


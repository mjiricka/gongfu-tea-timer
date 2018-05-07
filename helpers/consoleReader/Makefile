SOURCES=ConsoleReader

CC=g++
FLAGS=-I $(SRC_DIR) -Wall -g
SRC_DIR=../../src/
SOURCES_PATH=$(addsuffix .cpp, $(addprefix $(SRC_DIR), $(SOURCES)))

all: consoleReader

consoleReader: main.cpp $(SOURCES_PATH)
	$(CC) $(FLAGS) main.cpp $(SOURCES_PATH) -o consoleReader

clean:
	rm -f consoleReader


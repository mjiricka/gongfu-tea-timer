SOURCES=ConsoleReader

CC=g++
FLAGS=-I $(SRC_DIR) -Wall -g
SRC_DIR=../../src/
SOURCES_PATH=$(addsuffix .cpp, $(addprefix $(SRC_DIR), $(SOURCES)))

all: consoleReader.out

consoleReader.out: main.cpp $(SOURCES_PATH)
	$(CC) $(FLAGS) main.cpp $(SOURCES_PATH) -o consoleReader.out

clean:
	rm -f consoleReader.out


SOURCES=Printer Utils

CC=g++
FLAGS=-I $(SRC_DIR) -Wall -g
SRC_DIR=../../src/
SOURCES_PATH=$(addsuffix .cpp, $(addprefix $(SRC_DIR), $(SOURCES)))

all: printer.out

printer.out: main.cpp $(SOURCES_PATH)
	$(CC) $(FLAGS) main.cpp $(SOURCES_PATH) -o printer.out

clean:
	rm -f printer.out


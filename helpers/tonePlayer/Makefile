SOURCES=TonePlayer

CC=g++
FLAGS=-I $(SRC_DIR) -Wall -g
SRC_DIR=../../src/
LIBS=-lao
SOURCES_PATH=$(addsuffix .cpp, $(addprefix $(SRC_DIR), $(SOURCES)))

all: tonePlayer

tonePlayer: main.cpp $(SOURCES_PATH)
	$(CC) $(LIBS) $(FLAGS) main.cpp $(SOURCES_PATH) -o tonePlayer

clean:
	rm -f tonePlayer


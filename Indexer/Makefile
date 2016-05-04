CC=g++-4.8
OP=-O2 -std=c++11 -Wall
OBJ_DIR=./bin
SRC_DIR=./src

all: prep build

build: main
	$(CC) $(OBJ_DIR)/main.o -o main $(OP)

main:
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP)

prep:
	clear
	mkdir -p $(OBJ_DIR)
	mkdir -p ./documents

clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o
  

CC=g++-4.8
OP=-O2 -std=c++11 -Wall
SRC_DIR=./src
OBJ_DIR=./bin


all: prep build


build: main externalsorter triple
	$(CC) $(OBJ_DIR)/*.o -o main $(OP)


main: externalsorter
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP)


externalsorter: triple
	$(CC) -c $(SRC_DIR)/externalsorter.cpp -o $(OBJ_DIR)/externalsorter.o $(OP)


triple:
	$(CC) -c $(SRC_DIR)/triple.cpp -o $(OBJ_DIR)/triple.o $(OP)


prep:
	clear
	mkdir -p $(OBJ_DIR)
	mkdir -p ./.tmp


clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o
	rm -f ./.tmp/*
  

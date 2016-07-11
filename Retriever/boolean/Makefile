CC=g++
OP=-O2 -std=c++11 -Wall
OBJ_DIR=./bin
BASE_OBJ_DIR=../base
SRC_DIR=./src


all: prep build


build: main base retriever
	$(CC) $(OBJ_DIR)/*.o $(BASE_OBJ_DIR)/*.o -o main $(OP)


main: retriever base
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP)


retriever: base
	$(CC) -c $(SRC_DIR)/retriever.cpp -o $(OBJ_DIR)/retriever.o $(OP)

base:
	cd ../base && make

prep:
	clear
	mkdir -p $(OBJ_DIR)
  

clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o
  

CC=g++-4.8
OP=-O2 -std=c++11 -Wall
OBJ_DIR=./bin
SRC_DIR=./src


all: prep build


build: main document retriever
	$(CC) $(OBJ_DIR)/*.o -o main $(OP)


main: retriever document
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP)


retriever: document
	$(CC) -c $(SRC_DIR)/retriever.cpp -o $(OBJ_DIR)/retriever.o $(OP)


document:
	$(CC) -c $(SRC_DIR)/document.cpp -o $(OBJ_DIR)/document.o $(OP)


prep:
	clear
	mkdir -p $(OBJ_DIR)
  

clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o
  

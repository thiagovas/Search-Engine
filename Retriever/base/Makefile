CC=g++
OP=-O2 -std=c++11 -Wall
OBJ_DIR=.
SRC_DIR=.


all: prep build


build: util document


util:
	$(CC) -c $(SRC_DIR)/util.cpp -o $(OBJ_DIR)/util.o $(OP)


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
  

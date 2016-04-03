CC=g++-5
OP=-O2 -std=c++11 -Wall -lcurl
OBJ_DIR=./bin
SRC_DIR=./src

all: prep build

build: main crawler utils scheduler parser
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/crawler.o $(OBJ_DIR)/scheduler.o $(OBJ_DIR)/parser.o -o main $(OP)

main: crawler
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP)

crawler: scheduler parser utils
	$(CC) -c $(SRC_DIR)/crawler.cpp -o $(OBJ_DIR)/crawler.o $(OP)

parser: utils
	$(CC) -c $(SRC_DIR)/parser.cpp -o $(OBJ_DIR)/parser.o $(OP)

utils:
	$(CC) -c $(SRC_DIR)/utils.cpp -o $(OBJ_DIR)/utils.o $(OP)

scheduler: utils
	$(CC) -c $(SRC_DIR)/scheduler.cpp -o $(OBJ_DIR)/scheduler.o $(OP)


prep:
	clear
	mkdir -p $(OBJ_DIR)

clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o


CC=g++
OP=-O2 -std=c++11 -Wall -lcurl
OBJ_DIR=./bin
SRC_DIR=./src

all: prep build

build: main crawler utils scheduler parser
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/crawler.o $(OBJ_DIR)/scheduler.o $(OBJ_DIR)/parser.o -o main $(OP)

main:
	$(CC) -c $(SRC_DIR)/main.cc -o $(OBJ_DIR)/main.o $(OP)

crawler: scheduler
	$(CC) -c $(SRC_DIR)/crawler.cc -o $(OBJ_DIR)/crawler.o $(OP)

parser:
	$(CC) -c $(SRC_DIR)/parser.cc -o $(OBJ_DIR)/parser.o $(OP)

utils:
	$(CC) -c $(SRC_DIR)/utils.cc -o $(OBJ_DIR)/utils.o $(OP)

scheduler: utils
	$(CC) -c $(SRC_DIR)/scheduler.cc -o $(OBJ_DIR)/scheduler.o $(OP)


prep:
	clear
	mkdir -p $(OBJ_DIR)

clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o


CC=g++
OP=-L./chilkat/lib -O2 -std=c++11 -Wall -lpthread -lchilkat-9.5.0 -lresolv -pthread -Wl,--no-as-needed
IOP=-I./chilkat/include
BINLIB=./chilkat/lib/libchilkat-9.5.0.so
OBJ_DIR=./bin
SRC_DIR=./src

all: prep build

build: main crawler scheduler utils dumper binaryheap
	$(CC) $(IOP) $(OBJ_DIR)/main.o $(OBJ_DIR)/crawler.o $(OBJ_DIR)/scheduler.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/dumper.o $(OBJ_DIR)/binaryheap.o $(BINLIB) -o main $(OP)

main: crawler
	$(CC) $(IOP) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP)

crawler: scheduler utils dumper
	$(CC) $(IOP) -c $(SRC_DIR)/crawler.cpp -o $(OBJ_DIR)/crawler.o $(OP)

scheduler: utils binaryheap
	$(CC) $(IOP) -c $(SRC_DIR)/scheduler.cpp -o $(OBJ_DIR)/scheduler.o $(OP)

utils:
	$(CC) $(IOP) -c $(SRC_DIR)/utils.cpp -o $(OBJ_DIR)/utils.o $(OP)

dumper:
	$(CC) $(IOP) -c $(SRC_DIR)/dumper.cpp -o $(OBJ_DIR)/dumper.o $(OP)

binaryheap:
	$(CC) -c $(SRC_DIR)/binaryheap.cpp -o $(OBJ_DIR)/binaryheap.o $(OP)


prep:
	clear
	mkdir -p $(OBJ_DIR)
	mkdir -p ./documents

clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o
  

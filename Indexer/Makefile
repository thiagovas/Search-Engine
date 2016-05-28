CC=g++-4.8
OP=-O2 -std=c++11 -Wall
GUMBO_OP = `pkg-config --libs --cflags gumbo`
ICU_OP = `pkg-config --libs --cflags icu-uc icu-io`
OBJ_DIR=./bin
SRC_DIR=./src


all: prep build


build: main compressor externalsorter parser vocabulary indexer
	$(CC) $(OBJ_DIR)/*.o -o main $(OP) $(GUMBO_OP) $(ICU_OP)


main: parser compressor externalsorter vocabulary indexer
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(OP) $(GUMBO_OP) $(ICU_OP)


indexer: vocabulary parser
	$(CC) -c $(SRC_DIR)/indexer.cpp -o $(OBJ_DIR)/indexer.o $(OP) $(ICU_OP)


compressor:
	$(CC) -c $(SRC_DIR)/compressor.cpp -o $(OBJ_DIR)/compressor.o $(OP)


externalsorter:
	$(CC) -c $(SRC_DIR)/externalsorter.cpp -o $(OBJ_DIR)/externalsorter.o $(OP)


parser:
	$(CC) -c $(SRC_DIR)/parser.cpp -o $(OBJ_DIR)/parser.o $(OP) $(GUMBO_OP) $(ICU_OP)


vocabulary:
	$(CC) -c $(SRC_DIR)/vocabulary.cpp -o $(OBJ_DIR)/vocabulary.o $(OP) $(ICU_OP)



prep:
	clear
	mkdir -p $(OBJ_DIR)
	mkdir -p ./documents
	mkdir -p ./.tmp


clean:
	clear
	rm -f main
	rm -rf *~
	rm -rf $(OBJ_DIR)/*.o
	rm -f ./.tmp/*
  

VERSION = 5.4
CC      = /usr/bin/g++
CXXFLAGS=-g -std=c++14 -Wall -pedantic

OBJ_simple_example = simple_example.o
BIN_simple_example = simple_example

se: $(OBJ_simple_example)
	$(CC) -o $(BIN_simple_example) $(OBJ_simple_example)
	./$(BIN_simple_example)


OBJ_bedingung = bedingung.o
BIN_bedingung = bedingung

expr: $(OBJ_bedingung)
	$(CC) -o $(BIN_bedingung) $(OBJ_bedingung)
	./$(BIN_bedingung)

OBJ_enable = enable.o
BIN_enable = enable

std: $(OBJ_enable)
	$(CC) -o $(BIN_enable) $(OBJ_enable)
	./$(BIN_enable)

.PHONY: clean
clean:
	rm -rf $(BIN_simple_example) $(OBJ_simple_example)
	rm -rf $(OBJ_bedingung) $(BIN_bedingung)
	rm -rf $(OBJ_enable) $(BIN_enable)



OBJ_copyTest = copyTest.o
BIN_copyTest = copyTest
copyTest: $(OBJ_copyTest)
		$(CC) -o $(BIN_copyTest) $(OBJ_copyTest)
		./$(BIN_copyTest)

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/poker.o $(OBJ)/card.o
HDRS = $(INC)/card.hpp
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ./analisamem/bin/analisamem
EXE = $(BIN)/poker

$(BIN)/poker: $(OBJS)
	$(CC) -pg -o $(BIN)/poker $(OBJS) $(LIBS)

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp 

$(OBJ)/card.o: $(HDRS) $(SRC)/card.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/card.o $(SRC)/card.cpp 

clean:
	rm $(OBJ)/*.o $(BIN)/poker
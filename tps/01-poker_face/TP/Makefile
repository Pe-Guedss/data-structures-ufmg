CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/poker.o $(OBJ)/card.o $(OBJ)/deck.o $(OBJ)/hand.o $(OBJ)/player.o $(OBJ)/queue.o
HDRS = $(INC)/card.hpp $(INC)/deck.hpp $(INC)/hand.hpp $(INC)/player.hpp $(INC)/queue.hpp
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ./analisamem/bin/analisamem
EXE = $(BIN)/poker

$(BIN)/poker: $(OBJS)
	$(CC) -pg -o $(BIN)/poker $(OBJS) $(LIBS)

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp 

$(OBJ)/card.o: $(HDRS) $(SRC)/card.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/card.o $(SRC)/card.cpp 

$(OBJ)/deck.o: $(HDRS) $(SRC)/deck.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/deck.o $(SRC)/deck.cpp 

$(OBJ)/hand.o: $(HDRS) $(SRC)/hand.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/hand.o $(SRC)/hand.cpp
	
$(OBJ)/player.o: $(HDRS) $(SRC)/player.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/player.o $(SRC)/player.cpp

$(OBJ)/queue.o: $(HDRS) $(SRC)/queue.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/queue.o $(SRC)/queue.cpp

clean:
	rm $(OBJ)/*.o $(BIN)/poker
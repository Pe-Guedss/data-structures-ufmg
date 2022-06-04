CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/poker.o $(OBJ)/card.o $(OBJ)/deck.o $(OBJ)/hand.o $(OBJ)/player.o $(OBJ)/bets_queue.o $(OBJ)/round.o $(OBJ)/round_queue.o $(OBJ)/match.o
HDRS = $(INC)/card.hpp $(INC)/deck.hpp $(INC)/hand.hpp $(INC)/player.hpp $(INC)/bets_queue.hpp $(INC)/round.hpp $(INC)/round_queue.hpp $(INC)/match.hpp
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

$(OBJ)/bets_queue.o: $(HDRS) $(SRC)/bets_queue.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/bets_queue.o $(SRC)/bets_queue.cpp

$(OBJ)/round.o: $(HDRS) $(SRC)/round.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/round.o $(SRC)/round.cpp

$(OBJ)/round_queue.o: $(HDRS) $(SRC)/round_queue.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/round_queue.o $(SRC)/round_queue.cpp

$(OBJ)/match.o: $(HDRS) $(SRC)/match.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/match.o $(SRC)/match.cpp

clean:
	rm $(OBJ)/*.o $(BIN)/poker
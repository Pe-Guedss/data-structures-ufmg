CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/poker.o $(OBJ)/card.o $(OBJ)/deck.o $(OBJ)/hand.o $(OBJ)/player.o $(OBJ)/bets_queue.o $(OBJ)/round.o $(OBJ)/round_queue.o $(OBJ)/match.o $(OBJ)/memlog.o

HDRS = $(INC)/card.hpp $(INC)/deck.hpp $(INC)/hand.hpp $(INC)/player.hpp $(INC)/bets_queue.hpp $(INC)/round.hpp $(INC)/round_queue.hpp $(INC)/match.hpp $(INC)/memlog.hpp

CFLAGS = -pg -Wall -c -I$(INC)

ANALISAMEM = ./analisamem/bin/analisamem
EXE = $(BIN)/tp1.exe

EXEC_LOGS = analises/logs
GPROF = analises/gprof
# --------------------------------------------
MEM_INPUTS = analises/mem/partida
MEM_OUTPUTS = analises/mem/resultados
# --------------------------------------------
PERF_INPUTS = analises/perf/partidas
PERF_OUTPUTS = analises/perf/resultados

# folders:
# 	@echo criando estrutura de pastas para análise dos resultados.

# 	@ mkdir analises analises/mem analises/perf

# 	@ mkdir $(EXEC_LOGS) $(GPROF) $(MEM_INPUTS) $(MEM_OUTPUTS) $(PERF_INPUTS) $(PERF_OUTPUTS)

mem: $(EXE)
	$(EXE) -i $(MEM_INPUTS)/entrada.txt -o $(MEM_INPUTS)/saida.txt -p $(EXEC_LOGS)/memlog.out -l

	rm -rf $(MEM_OUTPUTS)

	mkdir $(MEM_OUTPUTS)

	$(ANALISAMEM) -i $(EXEC_LOGS)/memlog.out -p $(MEM_OUTPUTS)/mem_analysis

$(BIN)/tp1.exe: $(OBJS)
	$(CC) -pg -o $(BIN)/tp1.exe $(OBJS) $(LIBS)

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

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

clean:
	rm $(OBJ)/*.o $(BIN)/tp1.exe
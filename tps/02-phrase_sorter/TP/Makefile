CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/main.o $(OBJ)/lex-order.o

HDRS = $(INC)/lex-order.hpp

CFLAGS = -pg -Wall -c -I$(INC)

ANALISAMEM = ./analisamem/bin/analisamem
EXE = $(BIN)/tp2.exe

GPROF = analises/gprof
# --------------------------------------------
MEM_EXEC_LOGS = analises/mem/logs
MEM_INPUTS = analises/mem/partida
MEM_OUTPUTS = analises/mem/resultados
# --------------------------------------------
PERF_EXEC_LOGS = analises/perf/logs
PERF_INPUTS = analises/perf/partidas
PERF_OUTPUTS = analises/perf/resultados

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/lex-order.o: $(HDRS) $(SRC)/lex-order.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/lex-order.o $(SRC)/lex-order.cpp 
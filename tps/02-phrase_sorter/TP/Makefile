CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/main.o $(OBJ)/lex_order.o $(OBJ)/word.o $(OBJ)/word_list.o

HDRS = $(INC)/lex_order.hpp $(INC)/word.hpp $(INC)/word_list.hpp

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

$(OBJ)/lex_order.o: $(HDRS) $(SRC)/lex_order.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/lex_order.o $(SRC)/lex_order.cpp 

$(OBJ)/word.o: $(HDRS) $(SRC)/word.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/word.o $(SRC)/word.cpp 

$(OBJ)/word_list.o: $(HDRS) $(SRC)/word_list.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/word_list.o $(SRC)/word_list.cpp 
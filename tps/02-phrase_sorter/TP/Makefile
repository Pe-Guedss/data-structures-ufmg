CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/main.o $(OBJ)/lex_order.o $(OBJ)/word.o $(OBJ)/word_list.o $(OBJ)/phrase_sorter.o $(OBJ)/memlog.o

HDRS = $(INC)/lex_order.hpp $(INC)/word.hpp $(INC)/word_list.hpp $(INC)/phrase_sorter.hpp $(INC)/memlog.hpp

CFLAGS = -pg -Wall -c -I$(INC)

ANALISAMEM = ./analisamem/bin/analisamem
EXE = $(BIN)/tp2.exe

GPROF = analises/gprof
# --------------------------------------------
MEM_EXEC_LOGS = analises/mem/logs
MEM_INPUTS = analises/mem/in_out
MEM_OUTPUTS = analises/mem/resultados
# --------------------------------------------
PERF_EXEC_LOGS = analises/perf/logs
PERF_INPUTS = analises/perf/in_out
PERF_OUTPUTS = analises/perf/resultados

# folders:
# 	@echo criando estrutura de pastas para análise dos resultados.

# 	@ mkdir analises analises/mem analises/perf

# 	@ mkdir $(MEM_EXEC_LOGS) $(PERF_EXEC_LOGS) $(GPROF) $(MEM_INPUTS) $(MEM_OUTPUTS) $(PERF_INPUTS) $(PERF_OUTPUTS)

# mem: $(EXE)
# 	$(EXE) -i $(MEM_INPUTS)/entrada.txt -o $(MEM_INPUTS)/saida.txt -m 3 -s 4 -p $(MEM_EXEC_LOGS)/memlog.out -l

# 	rm -rf $(MEM_OUTPUTS)

# 	mkdir $(MEM_OUTPUTS)

# 	$(ANALISAMEM) -i $(MEM_EXEC_LOGS)/memlog.out -p $(MEM_OUTPUTS)/mem_analysis

# perf: $(EXE)
# 	$(EXE) -i $(PERF_INPUTS)/entrada_2000.out -o $(PERF_INPUTS)/saida_2000.out -p $(PERF_EXEC_LOGS)/perf_res_2000.out

# 	$(EXE) -i $(PERF_INPUTS)/entrada_4000.out -o $(PERF_INPUTS)/saida_4000.out -p $(PERF_EXEC_LOGS)/perf_res_4000.out
	
# 	$(EXE) -i $(PERF_INPUTS)/entrada_6000.out -o $(PERF_INPUTS)/saida_6000.out -p $(PERF_EXEC_LOGS)/perf_res_6000.out

# 	$(EXE) -i $(PERF_INPUTS)/entrada_8000.out -o $(PERF_INPUTS)/saida_8000.out -p $(PERF_EXEC_LOGS)/perf_res_8000.out
	
# 	$(EXE) -i $(PERF_INPUTS)/entrada_10000.out -o $(PERF_INPUTS)/saida_10000.out -p $(PERF_EXEC_LOGS)/perf_res_10000.out

# gprof: $(EXE)
# 	$(EXE) -i $(PERF_INPUTS)/entrada_10000.out -o $(PERF_INPUTS)/saida_10000.out -p $(GPROF)/perf_res_10000.out
# 	gprof $(EXE) gmon.out > $(GPROF)/perf_res_10000.txt

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

$(OBJ)/phrase_sorter.o: $(HDRS) $(SRC)/phrase_sorter.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/phrase_sorter.o $(SRC)/phrase_sorter.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp 

clean:
	rm $(OBJ)/*.o $(EXE)
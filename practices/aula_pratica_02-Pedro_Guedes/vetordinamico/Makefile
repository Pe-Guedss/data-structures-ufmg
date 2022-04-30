#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa vetop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2022-04-01 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/vetop.o $(OBJ)/vet.o $(OBJ)/memlog.o
HDRS = $(INC)/vet.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/vetop

all:  mem perf gprof

mem: $(EXE)
	$(EXE) -d 20 -s -p /tmp/somalog.out -l 
	rm -rf /tmp/somadin
	mkdir /tmp/somadin
	$(ANALISAMEM) -i /tmp/somalog.out -p /tmp/somadin/somadin
	$(EXE) -d 20 -i -p /tmp/internolog.out -l 
	rm -rf /tmp/internodin
	mkdir /tmp/internodin
	$(ANALISAMEM) -i /tmp/internolog.out -p /tmp/internodin/internodin
	$(EXE) -d 20 -n -p /tmp/normalog.out -l 
	rm -rf /tmp/normadin
	mkdir /tmp/normadin
	$(ANALISAMEM) -i /tmp/normalog.out -p /tmp/normadin/normadin

perf: $(EXE)
	$(EXE) -d 50000000 -s -p /tmp/soma50M.out
	$(EXE) -d 50000000 -i -p /tmp/interno50M.out
	$(EXE) -d 50000000 -n -p /tmp/norma50M.out
	$(EXE) -d 100000000 -s -p /tmp/soma100M.out
	$(EXE) -d 100000000 -i -p /tmp/interno100M.out
	$(EXE) -d 100000000 -n -p /tmp/norma100M.out
	$(EXE) -d 150000000 -s -p /tmp/soma150M.out
	$(EXE) -d 150000000 -i -p /tmp/interno150M.out
	$(EXE) -d 150000000 -n -p /tmp/norma150M.out
	$(EXE) -d 200000000 -s -p /tmp/soma200M.out
	$(EXE) -d 200000000 -i -p /tmp/interno200M.out
	$(EXE) -d 200000000 -n -p /tmp/norma200M.out
	$(EXE) -d 250000000 -s -p /tmp/soma250M.out
	$(EXE) -d 250000000 -i -p /tmp/interno250M.out
	$(EXE) -d 250000000 -n -p /tmp/norma250M.out

gprof: $(BIN)/vetop
	$(EXE) -d 250000000 -s -p /tmp/soma250Mgprof.out 
	gprof $(EXE) gmon.out > /tmp/soma250Mgprof.txt
	$(EXE) -d 250000000 -i -p /tmp/interno250Mgprof.out 
	gprof $(EXE) gmon.out > /tmp/interno250Mgprof.txt
	$(EXE) -d 250000000 -n -p /tmp/norma250Mgprof.out 
	gprof $(EXE) gmon.out > /tmp/norma250Mgprof.txt
	

$(BIN)/vetop: $(OBJS)
	$(CC) -pg -o $(BIN)/vetop $(OBJS) $(LIBS)

$(OBJ)/vetop.o: $(HDRS) $(SRC)/vetop.c
	$(CC) $(CFLAGS) -o $(OBJ)/vetop.o $(SRC)/vetop.c 

$(OBJ)/vet.o: $(HDRS) $(SRC)/vet.c
	$(CC) $(CFLAGS) -o $(OBJ)/vet.o $(SRC)/vet.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

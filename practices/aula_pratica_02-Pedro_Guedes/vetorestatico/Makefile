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
	rm -rf /tmp/somaest
	mkdir /tmp/somaest
	$(ANALISAMEM) -i /tmp/somalog.out -p /tmp/somaest/somaest
	$(EXE) -d 20 -i -p /tmp/internolog.out -l 
	rm -rf /tmp/internoest
	mkdir /tmp/internoest
	$(ANALISAMEM) -i /tmp/internolog.out -p /tmp/internoest/internoest
	$(EXE) -d 20 -n -p /tmp/normalog.out -l 
	rm -rf /tmp/normaest
	mkdir /tmp/normaest
	$(ANALISAMEM) -i /tmp/normalog.out -p /tmp/normaest/normaest

perf: $(EXE)
	$(EXE) -d 60000 -s -p /tmp/soma60k.out
	$(EXE) -d 60000 -i -p /tmp/interno60k.out
	$(EXE) -d 60000 -n -p /tmp/norma60k.out
	$(EXE) -d 120000 -s -p /tmp/soma120k.out
	$(EXE) -d 120000 -i -p /tmp/interno120k.out
	$(EXE) -d 120000 -n -p /tmp/norma120k.out
	$(EXE) -d 180000 -s -p /tmp/soma180k.out
	$(EXE) -d 180000 -i -p /tmp/interno180k.out
	$(EXE) -d 180000 -n -p /tmp/norma180k.out
	$(EXE) -d 240000 -s -p /tmp/soma240k.out
	$(EXE) -d 240000 -i -p /tmp/interno240k.out
	$(EXE) -d 240000 -n -p /tmp/norma240k.out
	$(EXE) -d 300000 -s -p /tmp/soma300k.out
	$(EXE) -d 300000 -i -p /tmp/interno300k.out
	$(EXE) -d 300000 -n -p /tmp/norma300k.out

gprof: $(BIN)/vetop
	$(EXE) -d 300000 -s -p /tmp/soma300kgprof.out 
	gprof $(EXE) gmon.out > /tmp/soma300kgprof.txt
	$(EXE) -d 300000 -i -p /tmp/interno300kgprof.out 
	gprof $(EXE) gmon.out > /tmp/interno300kgprof.txt
	$(EXE) -d 300000 -n -p /tmp/norma300kgprof.out 
	gprof $(EXE) gmon.out > /tmp/norma300kgprof.txt
	

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

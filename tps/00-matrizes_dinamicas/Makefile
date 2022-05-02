#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
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
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ./analisamem/bin/analisamem

# Matrizes para análise de localidade e referência devem ser menores, portanto há uma diferenciação de diretórios de armazenamento dos ".txt" de matrizes
SOMALOGS = analises/soma/logs
SOMAGPROF = analises/soma/gprof
# --------------------------------------------
SOMAMATRIZESMEM = analises/soma/mem/matrizes
SOMAMEM = analises/soma/mem/resultados
# --------------------------------------------
SOMAMATRIZESPERF = analises/soma/perf/matrizes
SOMAPERF = analises/soma/perf/resultados


MULTLOGS = analises/mult/logs
MULTGPROF = analises/mult/gprof
# --------------------------------------------
MULTMATRIZESMEM = analises/mult/mem/matrizes
MULTMEM = analises/mult/mem/resultados
# --------------------------------------------
MULTMATRIZESPERF = analises/mult/perf/matrizes
MULTPERF = analises/mult/perf/resultados


TRANSLOGS = analises/trans/logs
TRANSGPROF = analises/trans/gprof
# --------------------------------------------
TRANSMATRIZESMEM = analises/trans/mem/matrizes
TRANSMEM = analises/trans/mem/resultados
# --------------------------------------------
TRANSMATRIZESPERF = analises/trans/perf/matrizes
TRANSPERF = analises/trans/perf/resultados

EXE = $(BIN)/matop


folders:
	@echo criando estrutura de pastas para análise dos resultados.

	@ mkdir analises

	@ mkdir analises/soma analises/soma/mem analises/soma/perf

	@ mkdir analises/mult analises/mult/mem analises/mult/perf

	@ mkdir analises/trans analises/trans/mem analises/trans/perf

	@ mkdir $(SOMALOGS) $(SOMAGPROF) $(SOMAMATRIZESMEM) $(SOMAMEM) $(SOMAMATRIZESPERF) $(SOMAPERF)

	@ mkdir $(MULTLOGS) $(MULTGPROF) $(MULTMATRIZESMEM) $(MULTMEM) $(MULTMATRIZESPERF) $(MULTPERF)

	@ mkdir $(TRANSLOGS) $(TRANSGPROF) $(TRANSMATRIZESMEM) $(TRANSMEM) $(TRANSMATRIZESPERF) $(TRANSPERF)


all: mem perf gprof

mem: $(EXE)
	$(EXE) -s -1 $(SOMAMATRIZESMEM)/m1.txt -2 $(SOMAMATRIZESMEM)/m2.txt -o $(SOMAMATRIZESMEM)/res.txt -p $(SOMALOGS)/somalog.out -l
	rm -rf $(SOMAMEM)
	mkdir $(SOMAMEM)
	$(ANALISAMEM) -i $(SOMALOGS)/somalog.out -p $(SOMAMEM)/somamat

	$(EXE) -m -1 $(MULTMATRIZESMEM)/m1.txt -2 $(MULTMATRIZESMEM)/m2.txt -o $(MULTMATRIZESMEM)/res.txt -p $(MULTLOGS)/multlog.out -l
	rm -rf $(MULTMEM)
	mkdir $(MULTMEM)
	$(ANALISAMEM) -i $(MULTLOGS)/multlog.out -p $(MULTMEM)/multmat

	$(EXE) -t -1 $(TRANSMATRIZESMEM)/m1.txt -o $(TRANSMATRIZESMEM)/res.txt -p $(TRANSLOGS)/transplog.out -l
	rm -rf $(TRANSMEM)
	mkdir $(TRANSMEM)
	$(ANALISAMEM) -i $(TRANSLOGS)/transplog.out -p $(TRANSMEM)/transmat

perf: $(EXE)
	$(EXE) -s -1 $(SOMAMATRIZESPERF)/m1_500.txt -2 $(SOMAMATRIZESPERF)/m2_500.txt -o $(SOMAMATRIZESPERF)/soma_res_500.txt -p $(SOMAPERF)/soma500.out

	$(EXE) -m -1 $(MULTMATRIZESPERF)/m1_500.txt -2 $(MULTMATRIZESPERF)/m2_500.txt -o $(MULTMATRIZESPERF)/mult_res_500.txt -p $(MULTPERF)/mult500.out

	$(EXE) -m -1 $(TRANSMATRIZESPERF)/m1_500.txt -o $(TRANSMATRIZESPERF)/transp_res_500.txt -p $(TRANSPERF)/transp500.out



	$(EXE) -s -1 $(SOMAMATRIZESPERF)/m1_600.txt -2 $(SOMAMATRIZESPERF)/m2_600.txt -o $(SOMAMATRIZESPERF)/soma_res_600.txt -p $(SOMAPERF)/soma600.out

	$(EXE) -m -1 $(MULTMATRIZESPERF)/m1_600.txt -2 $(MULTMATRIZESPERF)/m2_600.txt -o $(MULTMATRIZESPERF)/mult_res_600.txt -p $(MULTPERF)/mult600.out

	$(EXE) -m -1 $(TRANSMATRIZESPERF)/m1_600.txt -o $(TRANSMATRIZESPERF)/transp_res_600.txt -p $(TRANSPERF)/transp600.out



	$(EXE) -s -1 $(SOMAMATRIZESPERF)/m1_700.txt -2 $(SOMAMATRIZESPERF)/m2_700.txt -o $(SOMAMATRIZESPERF)/soma_res_700.txt -p $(SOMAPERF)/soma700.out

	$(EXE) -m -1 $(MULTMATRIZESPERF)/m1_700.txt -2 $(MULTMATRIZESPERF)/m2_700.txt -o $(MULTMATRIZESPERF)/mult_res_700.txt -p $(MULTPERF)/mult700.out

	$(EXE) -m -1 $(TRANSMATRIZESPERF)/m1_700.txt -o $(TRANSMATRIZESPERF)/transp_res_700.txt -p $(TRANSPERF)/transp700.out



	$(EXE) -s -1 $(SOMAMATRIZESPERF)/m1_800.txt -2 $(SOMAMATRIZESPERF)/m2_800.txt -o $(SOMAMATRIZESPERF)/soma_res_800.txt -p $(SOMAPERF)/soma800.out

	$(EXE) -m -1 $(MULTMATRIZESPERF)/m1_800.txt -2 $(MULTMATRIZESPERF)/m2_800.txt -o $(MULTMATRIZESPERF)/mult_res_800.txt -p $(MULTPERF)/mult800.out

	$(EXE) -m -1 $(TRANSMATRIZESPERF)/m1_800.txt -o $(TRANSMATRIZESPERF)/transp_res_800.txt -p $(TRANSPERF)/transp800.out



	$(EXE) -s -1 $(SOMAMATRIZESPERF)/m1_900.txt -2 $(SOMAMATRIZESPERF)/m2_900.txt -o $(SOMAMATRIZESPERF)/soma_res_900.txt -p $(SOMAPERF)/soma900.out

	$(EXE) -m -1 $(MULTMATRIZESPERF)/m1_900.txt -2 $(MULTMATRIZESPERF)/m2_900.txt -o $(MULTMATRIZESPERF)/mult_res_900.txt -p $(MULTPERF)/mult900.out

	$(EXE) -m -1 $(TRANSMATRIZESPERF)/m1_900.txt -o $(TRANSMATRIZESPERF)/transp_res_900.txt -p $(TRANSPERF)/transp900.out

gprof: $(BIN)/matop
	$(EXE) -s -1 $(SOMAMATRIZESPERF)/m1_900.txt -2 $(SOMAMATRIZESPERF)/m2_900.txt -o $(SOMAMATRIZESPERF)/soma_res_900.txt -p $(SOMAGPROF)/soma900gprof.out
	gprof $(EXE) gmon.out > $(SOMAGPROF)/soma900gprof.txt

	$(EXE) -m -1 $(MULTMATRIZESPERF)/m1_900.txt -2 $(MULTMATRIZESPERF)/m2_900.txt -o $(MULTMATRIZESPERF)/mult_res_900.txt -p $(MULTGPROF)/mult900gprof.out
	gprof $(EXE) gmon.out > $(MULTGPROF)/mult900gprof.txt

	$(EXE) -m -1 $(TRANSMATRIZESPERF)/m1_900.txt -o $(TRANSMATRIZESPERF)/transp_res_900.txt -p $(TRANSGPROF)/transp900gprof.out
	gprof $(EXE) gmon.out > $(TRANSGPROF)/transp900gprof.txt
	

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

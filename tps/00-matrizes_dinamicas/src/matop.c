#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// definicoes de operacoes a serem testadas
#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3

// variaveis globais para opcoes
static int opescolhida;
char lognome[100];
int regmem;

char matrixPath1[100], matrixPath2[100], matrixPathRes[100];

// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
void uso() {
    fprintf(stderr, "matop\n");
    fprintf(stderr, "\t-s \t(somar matrizes) \n");
    fprintf(stderr, "\t-m \t(multiplicar matrizes) \n");
    fprintf(stderr, "\t-t \t(transpor matriz)\n");
    fprintf(stderr, "\t-1 <arq1.txt>\t(caminho para arquivo de texto contendo a matriz 1)\n");
    fprintf(stderr, "\t-2 <arq2.txt>\t(caminho para arquivo de texto contendo a matriz 2)\n");
    fprintf(stderr, "\t-o <arq_res.txt>\t(caminho para arquivo de texto onde sera armazenada a matriz de resultado da operacao)\n");
    fprintf(stderr, "\t-p <arq>\t(arquivo de registro de acesso)\n");
    fprintf(stderr, "\t-l \t(registrar acessos a memoria)\n");
}


// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
void parse_args(int argc, char **argv) {
    // variaveis externas do getopt
    extern char *optarg;
    extern int optind;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    opescolhida = -1;
    regmem = 0;
    lognome[0] = matrixPath1[0] = matrixPath2[0] = matrixPathRes[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while (( c = getopt(argc, argv, "smtp:1:2:o:lh") ) != EOF){
        switch(c) {
            case 'm':
                avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = OPMULTIPLICAR;
            break;

            case 's':
                avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = OPSOMAR;
            break;

            case 't':
                avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = OPTRANSPOR;
            break;

            case '1':
                avisoAssert(matrixPath1[0]==0, "Ja havia sido informado um arquivo para a matriz 1");
                strcpy(matrixPath1, optarg);
            break;

            case '2':
                avisoAssert(matrixPath2[0]==0, "Ja havia sido informado um arquivo para a matriz 2");
                strcpy(matrixPath2, optarg);
            break;

            case 'o':
                avisoAssert(matrixPathRes[0]==0, "Ja havia sido informado um arquivo para a matriz de output");
                strcpy(matrixPathRes, optarg);
            break;

            case 'p': 
                strcpy(lognome, optarg);
            break;

            case 'l': 
                regmem = 1;
            break;
            
            default:
                uso();
                exit(1);
        }
    }

    // verificacao da consistencia das opcoes
    erroAssert(opescolhida > 0, "matop - necessario escolher operacao");
    erroAssert( strlen(lognome) > 0, "matop - nome de arquivo de registro de acesso tem que ser definido" );
}


// Descricao: programa principal para execucao de operacoes de matrizes 
// Entrada: argc e argv
// Saida: depende da operacao escolhida
int main(int argc, char **argv) {
    // ate 3 matrizes sao utilizadas, dependendo da operacao
    mat_tipo a, b, c;

    // avaliar linha de comando
    parse_args(argc,argv);

    // iniciar registro de acesso
    iniciaMemLog(lognome);

    // ativar ou nao o registro de acesso
    if (regmem){ 
        ativaMemLog();
    }
    else{
        desativaMemLog();
    }

    // execucao dependente da operacao escolhida
    switch (opescolhida){
        // cria matrizes a e b aleatorias, que sao somadas para a matriz c
        // matriz c é impressa e todas as matrizes sao destruidas
        case OPSOMAR:
            erroAssert(matrixPath1[0] != 0, "Deve ser informado um arquivo de texto contendo a matriz 1.");
            erroAssert(matrixPath2[0] != 0, "Deve ser informado um arquivo de texto contendo a matriz 2.");
            erroAssert(matrixPathRes[0] != 0, "Deve ser informado um arquivo de texto para armazenar o resultado da operação.");

            defineFaseMemLog(0);
            criaMatrizInput(&a, matrixPath1, 0);
            leMatrizDoTxt(&a);
            criaMatrizInput(&b, matrixPath2, 1);
            leMatrizDoTxt(&b);
            criaMatrizOutput(&c, matrixPathRes, a.tamX, a.tamY, 2);
            inicializaMatrizNula(&c);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            acessaMatriz(&b);
            acessaMatriz(&c);
            somaMatrizes(&a,&b,&c);

            defineFaseMemLog(2);
            acessaMatriz(&c);
            matrizParaTxt(&c);
            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
        break;

        // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
        // matriz c é impressa e todas as matrizes sao destruidas
        case OPMULTIPLICAR:
            erroAssert(matrixPath1[0] != 0, "Deve ser informado um arquivo de texto contendo a matriz 1.");
            erroAssert(matrixPath2[0] != 0, "Deve ser informado um arquivo de texto contendo a matriz 2.");
            erroAssert(matrixPathRes[0] != 0, "Deve ser informado um arquivo de texto para armazenar o resultado da operação.");

            defineFaseMemLog(0);
            criaMatrizInput(&a, matrixPath1, 0);
            leMatrizDoTxt(&a);
            criaMatrizInput(&b, matrixPath2, 1);
            leMatrizDoTxt(&b);
            criaMatrizOutput(&c, matrixPathRes, a.tamX, b.tamY, 2);
            inicializaMatrizNula(&c);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            acessaMatriz(&b);
            acessaMatriz(&c);
            multiplicaMatrizes(&a,&b,&c);

            defineFaseMemLog(2);
            acessaMatriz(&c);
            matrizParaTxt(&c);
            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
        break;

            // cria matriz a aleatoria, que e transposta, impressa e destruida
        case OPTRANSPOR:
            erroAssert(matrixPath1[0] != 0, "Deve ser informado um arquivo de texto contendo a matriz 1.");
            erroAssert(matrixPathRes[0] != 0, "Deve ser informado um arquivo de texto para armazenar o resultado da operação.");

            defineFaseMemLog(0);
            criaMatrizInput(&a, matrixPath1, 0);
            leMatrizDoTxt(&a);
            criaMatrizOutput(&c, matrixPathRes, a.tamY, a.tamX, 1);
            inicializaMatrizNula(&c);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            transpoeMatriz(&a, &c);

            defineFaseMemLog(2);
            acessaMatriz(&a);
            matrizParaTxt(&c);
            destroiMatriz(&a);
            destroiMatriz(&c);
        break;

        // nao deve ser executado, pois ha um erroAssert em parse_args
        default:
            uso();
            exit(1);
    }

    // conclui registro de acesso
    return finalizaMemLog();
}


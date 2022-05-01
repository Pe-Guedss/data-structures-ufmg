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

char *matrixPath1, *matrixPath2, *matrixPathRes;

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
    lognome[0] = 0;

    matrixPath1 = matrixPath2 = matrixPathRes = NULL;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while (( c = getopt(argc, argv, "smtp:1:o:lh") ) != EOF){
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
                avisoAssert(matrixPath1==NULL, "Ja havia sido informado um arquivo para a matriz 1");
                matrixPath1 = optarg;
            break;

            case '2':
                avisoAssert(matrixPath2==NULL, "Ja havia sido informado um arquivo para a matriz 2");
                matrixPath2 = optarg;
            break;

            case 'o':
                avisoAssert(matrixPathRes==NULL, "Ja havia sido informado um arquivo para a matriz o");
                matrixPathRes = optarg;
            break;

            case 'p': 
                strcpy(lognome,optarg);
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
            defineFaseMemLog(0);
            criaMatriz(&a,0);
            inicializaMatrizAleatoria(&a);
            criaMatriz(&b,1);
            inicializaMatrizAleatoria(&b);
            criaMatriz(&c,2);
            inicializaMatrizNula(&c);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            acessaMatriz(&b);
            acessaMatriz(&c);
            somaMatrizes(&a,&b,&c);

            defineFaseMemLog(2);
            acessaMatriz(&c);
            if (regmem) imprimeMatriz(&c);
            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
        break;

        // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
        // matriz c é impressa e todas as matrizes sao destruidas
        case OPMULTIPLICAR:
            defineFaseMemLog(0);
            criaMatriz(&a,0);
            inicializaMatrizAleatoria(&a);
            criaMatriz(&b,1);
            inicializaMatrizAleatoria(&b);
            criaMatriz(&c,2);
            inicializaMatrizNula(&c);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            acessaMatriz(&b);
            acessaMatriz(&c);
            multiplicaMatrizes(&a,&b,&c);

            defineFaseMemLog(2);
            acessaMatriz(&c);
            if (regmem) imprimeMatriz(&c);
            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
        break;

            // cria matriz a aleatoria, que e transposta, impressa e destruida
        case OPTRANSPOR:
            defineFaseMemLog(0);
            criaMatriz(&a,0);
            inicializaMatrizAleatoria(&a);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            transpoeMatriz(&a);

            defineFaseMemLog(2);
            acessaMatriz(&a);
            if (regmem) imprimeMatriz(&a);
            destroiMatriz(&a);
        break;

        // nao deve ser executado, pois ha um erroAssert em parse_args
        default:
            uso();
            exit(1);
    }

    // conclui registro de acesso
    return finalizaMemLog();
}


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x, y) (x += y, y = x - y, x -= y)

// Descricao: Lê o arquivo de texto armazenado na estrutura da matriz e define o tamanhho dela com base na primeira linha do mesmo
// Entrada: mat
// Saída: mat
void dimensoesMatriz(mat_tipo *mat) {
    FILE *arq;
    int rows, columns;

    arq = fopen(mat->matrixPath, "r");
    erroAssert(arq != NULL, "Ocorreu um erro ao abrir o arquivo da matriz");

    fscanf(arq, "%d", &rows);
    fscanf(arq, "%d", &columns);

    // Verifica se as dimensões são válidas
    erroAssert(rows > 0, "As dimensões da matriz não podem ser nulas");
    erroAssert(columns > 0, "As dimensões da matriz não podem ser nulas");

    mat->tamX = rows;
    mat->tamY = columns;

    fclose(arq);
}

// Descricao: cria matriz de input de acordo com informações do txt
// Entrada: mat, matrixPath, id
// Saida: mat
void criaMatrizInput(mat_tipo *mat, char *matrixPath, int id) {
    // Verifica se matrixPath contem um caminho não nulo
    erroAssert(matrixPath != NULL, "O caminho para a matriz precisa ser especificado");
    mat->matrixPath = matrixPath;

    // Inicializa dimensões da matriz
    dimensoesMatriz(mat);

    // Aloca as linhas matriz de acordo com as dimensões especificadas
    mat->m = (double**)malloc(mat->tamX * sizeof(double*));
    erroAssert(mat->m != NULL, "Ocorreu um erro ao alocar a matriz");

    for (int i = 0; i < mat->tamX; i++) {
        // Aloca as colunas da matriz de acordo com as dimensões especificadas
        mat->m[i] = (double*)malloc(mat->tamY * sizeof(double));
        erroAssert(mat->m[i] != NULL, "Ocorreu um erro ao alocar a matriz");
    }

    // inicializa o identificador da matriz, para rastreamento
    mat->id = id;
}

// Descricao: cria matriz de output com dimensões informadas previamente
// Entrada: mat, matrixPath, tamX, tamY, id
// Saida: mat
void criaMatrizOutput(mat_tipo *mat, char *matrixPath, int tamX, int tamY, int id) {
    // Verifica se matrixPath contem um caminho não nulo
    erroAssert(matrixPath != NULL, "O caminho para a matriz precisa ser especificado");
    mat->matrixPath = matrixPath;

    // Verifica se as dimensões são válidas
    erroAssert(tamX > 0, "As dimensões da matriz não podem ser nulas");
    mat->tamX = tamX;
    erroAssert(tamY > 0, "As dimensões da matriz não podem ser nulas");
    mat->tamY = tamY;

    // Aloca as linhas matriz de acordo com as dimensões especificadas
    mat->m = (double**)malloc(mat->tamX * sizeof(double*));
    erroAssert(mat->m != NULL, "Ocorreu um erro ao alocar a matriz");
    
    for (int i = 0; i < mat->tamX; i++) {
        // Aloca as colunas da matriz de acordo com as dimensões especificadas
        mat->m[i] = (double*)malloc(mat->tamY * sizeof(double));
        erroAssert(mat->m[i] != NULL, "Ocorreu um erro ao alocar a matriz");
    }

    // inicializa o identificador da matriz, para rastreamento
    mat->id = id;
}

// Descricao: inicializa mat com valores nulos 
// Entrada: mat
// Saida: mat
void inicializaMatrizNula(mat_tipo *mat) {
    erroAssert(mat->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");

    int i, j;

    // inicializa todos os elementos da matriz com 0, por seguranca 
    for (i = 0; i < mat->tamX; i++){
        for(j = 0; j < mat->tamY; j++){
            mat->m[i][j] = 0;
            ESCREVEMEMLOG( (long int) ( &(mat->m[i][j]) ), sizeof(double), mat->id );
        }
    }
}

// Descricao: inicializa mat com os valores do txt
// Entrada: mat 
// Saida: mat
void leMatrizDoTxt(mat_tipo *mat) {
    erroAssert(mat->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");

    int i, j;
    FILE *arq;

    double num;
    int auxDims;

    // inicializa a matriz com valores nulos, por seguranca
    inicializaMatrizNula(mat);
    
    arq = fopen(mat->matrixPath, "r");
    erroAssert(arq != NULL, "Ocorreu um erro ao abrir o arquivo da matriz");

    fscanf(arq, "%d %d", &auxDims, &auxDims);

    while (!feof(arq)) {
        for (i = 0; i < mat->tamX; i++) {
            for(j = 0; j < mat->tamY; j++) {
                // Armazena o elemento do txt na matriz
                erroAssert(fscanf(arq, "%lf ", &num) == 1, "Matriz informada não bate com as especificações ditas (menor)");
                mat->m[i][j] = num;
                ESCREVEMEMLOG( (long int) ( &(mat->m[i][j]) ), sizeof(double), mat->id );
            }
        }

        erroAssert(fscanf(arq, "%lf ", &num) == -1, "Matriz informada não bate com as especificações ditas (maior)");
    }

    fclose(arq);
}

// Descricao: acessa mat para fins de registro de acesso
// Entrada: mat
// Saida: mat
double acessaMatriz(mat_tipo *mat) {
    erroAssert(mat->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");

    int i, j;

    double aux, s = 0.0;
    
    for (i = 0; i < mat->tamX; i++){
        for(j = 0; j < mat->tamY; j++){
            aux = mat->m[i][j];
            s += aux;
            LEMEMLOG( (long int) ( &(mat->m[i][j]) ), sizeof(double), mat->id );
        }
    }
    return s; // apenas para evitar que acesso seja eliminado
}

// Descricao: Itera pelos elementos de "src" copiando-os para "dst"
// Entrada: src e dst
// Saida: dst
void copiaMatrizes(mat_tipo *src, mat_tipo *dst) {
    erroAssert(src->m != NULL, "Matriz informada como fonte ainda não foi alocada, portanto, não pode ser inicializada");
    erroAssert(dst->m != NULL, "Matriz informada como destino ainda não foi alocada, portanto, não pode ser inicializada");

    int row, column;

    dst->tamX = src->tamX;
    dst->tamY = src->tamY;
    
    for (row = 0; row < src->tamX; row++) {
        for (column = 0; column < src->tamY; column++) {
            dst->m[row][column] = src->m[row][column];
            
            LEMEMLOG((long int)(&(src->m[row][column])),sizeof(double),src->id);
            ESCREVEMEMLOG((long int)(&(dst->m[row][column])),sizeof(double),dst->id);
        }
    }
}

// Descricao: escreve os elementos de src em seu respectivo arquivo de texto
// Entrada: src
// Saida: src->matrixPath.txt
void matrizParaTxt(mat_tipo *src) {
    erroAssert(src->m != NULL, "Matriz informada como fonte ainda não foi alocada, portanto, não pode ser inicializada");

    int i,j;

    FILE *matriz;

    matriz = fopen(src->matrixPath, "w");

    // Verificando se a abertura do arquivo ocorreu corretamente
    erroAssert(matriz != NULL, "Ocorreu um erro ao abrir o arquivo.");

    // copia as dimensões de src para o arquivo
    fprintf(matriz, "%d %d\n", src->tamX, src->tamY);
    
    // copia os elementos da matriz src
    for (i = 0; i < src->tamX; i++){
        for(j = 0; j < src->tamY; j++){
            fprintf(matriz, "%f ", src->m[i][j]);
            LEMEMLOG( (long int) ( &(src->m[i][j]) ), sizeof(double), src->id );
        }
        fprintf(matriz, "\n");
    }

    fclose(matriz);
}

// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c) {
    erroAssert(a->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");
    erroAssert(b->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");

    int i,j;

    // verifica se as dimensoes das matrizes a e b sao as mesmas
    erroAssert(a->tamX == b->tamX, "Dimensoes incompativeis");
    erroAssert(a->tamY == b->tamY, "Dimensoes incompativeis");

    // inicializa a matriz c garantindo a compatibilidade das dimensoes
    criaMatrizOutput(c, c->matrixPath, a->tamX, a->tamY, c->id);
    inicializaMatrizNula(c);

    // faz a soma elemento a elemento
    for (i = 0; i < a->tamX; i++){
        for(j = 0; j < a->tamY; j++){
            c->m[i][j] = a->m[i][j] + b->m[i][j];
            LEMEMLOG( (long int) ( &(a->m[i][j]) ), sizeof(double), a->id );
            LEMEMLOG( (long int) ( &(b->m[i][j]) ), sizeof(double), b->id );
            ESCREVEMEMLOG( (long int) ( &(c->m[i][j]) ), sizeof(double), c->id );
        }
    }
}

// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c) {
    erroAssert(a->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");
    erroAssert(b->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");

    int i,j,k;

    // verifica a compatibilidade das dimensoes 
    erroAssert( a->tamY == b->tamX, "Dimensoes incompativeis" );

    // cria e inicializa a matriz c
    criaMatrizOutput(c, c->matrixPath, a->tamX, b->tamY, c->id);
    inicializaMatrizNula(c);

    // realiza a multiplicacao de matrizes
    for (i = 0; i < c->tamX; i++){
        for (j = 0; j < c->tamY; j++){
            for (k = 0; k < a->tamY; k++){
                c->m[i][j] += a->m[i][k] * b->m[k][j];
                LEMEMLOG( (long int) ( &(a->m[i][k]) ), sizeof(double), a->id );
                LEMEMLOG( (long int) ( &(b->m[k][j]) ), sizeof(double), b->id );
                ESCREVEMEMLOG( (long int) ( &(c->m[i][j]) ), sizeof(double), c->id );
            }
        }
    }
}

// Descricao: transpoe a matriz a armazenando os valores em b
// Entrada: a
// Saida: b
void transpoeMatriz(mat_tipo *a, mat_tipo *b) {
    erroAssert(a->m != NULL, "Matriz informada ainda não foi alocada, portanto, não pode ser inicializada");

    int i, j;

    // cria e inicializa a matriz b
    criaMatrizOutput(b, b->matrixPath, a->tamY, a->tamX, b->id);
    inicializaMatrizNula(b);

    // faz a transposicao como se a matriz fosse quadrada
    for (i = 0; i < a->tamX; i++){
        for(j = 0; j < a->tamY; j++){
            b->m[j][i] = a->m[i][j];
            LEMEMLOG( (long int) ( &(a->m[i][j]) ), sizeof(double), a->id );
            ESCREVEMEMLOG( (long int) ( &(b->m[j][i]) ), sizeof(double), b->id );
        }
    }
}

// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
void destroiMatriz(mat_tipo *a) {
    int i;

    // apenas um aviso se a matriz for destruida mais de uma vez
    avisoAssert(a->m != NULL , "Matriz já foi desalocada");

    for (i = 0; i < a->tamX; i++) {
        free(a->m[i]);
        a->m[i] = NULL;
    }

    free(a->m);
    a->m = NULL;

    // torna as dimensoes invalidas
    a->id = a->tamX = a->tamY = -1;
}

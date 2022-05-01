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

// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty, id
// Saida: mat
void criaMatriz(mat_tipo *mat, char *matrixPath,  int id) {
    // Verifica se matrixPath contem um caminho não nulo
    erroAssert(matrixPath != NULL, "O caminho para a matriz precisa ser especificado");
    mat->matrixPath = matrixPath;

    // inicializa o identificador da matriz, para rastreamento
    mat->id = id;
}

// Descricao: inicializa mat com valores nulos 
// Entrada: mat
// Saida: mat
void inicializaMatrizNula(mat_tipo *mat) {
    int i, j;

    // inicializa todos os elementos da matriz com 0, por seguranca 
    for (i = 0; i < mat->tamX; i++){
        for(j = 0; j < mat->tamY; j++){
            mat->m[i][j] = 0;
            ESCREVEMEMLOG( (long int) ( &(mat->m[i][j]) ), sizeof(double), mat->id );
        }
    }
}

// Descricao: inicializa mat com valores aleatorios
// Entrada: mat 
// Saida: mat
void inicializaMatrizAleatoria(mat_tipo *mat) {
    int i, j;

    // inicializa a matriz com valores nulos, por seguranca
    inicializaMatrizNula(mat);
    
    // inicializa a parte alocada da matriz com valores aleatorios
    for (i = 0; i < mat->tamX; i++){
        for(j = 0; j < mat->tamY; j++){
            mat->m[i][j] = drand48()*INITRANDOMRANGE;
            ESCREVEMEMLOG( (long int) ( &(mat->m[i][j]) ), sizeof(double), mat->id );
        }
    }
}

// Descricao: acessa mat para fins de registro de acesso
// Entrada: mat
// Saida: mat
double acessaMatriz(mat_tipo *mat) {
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

// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Entrada: mat
// Saida: impressao na saida padrao (stdout) 
void imprimeMatriz(mat_tipo *mat) {
    int i,j;

    // imprime os identificadores de coluna
    printf("%9s", " ");
    for(j = 0; j < mat->tamY; j++){
        printf("%8d ", j);
    }
    printf("\n");

    // imprime as linhas
    for (i = 0; i < mat->tamX; i++) {
        printf("%8d ", i);
        for(j = 0; j < mat->tamY; j++) {
            printf("%8.2f ", mat->m[i][j]);
            LEMEMLOG( (long int) ( &(mat->m[i][j]) ), sizeof(double), mat->id );
        }
        printf("\n");
    }
}

// Descricao: atribui o valor v ao elemento (x,y) de mat
// Entrada: mat, x, y, v
// Saida: mat
void escreveElemento(mat_tipo *mat, int x, int y, double v) {
    // verifica se x e y sao validos
    erroAssert( (x < 0) || (x >= mat->tamX), "Indice invalido" );
    erroAssert( (y < 0) || (y >= mat->tamY), "Indice invalido" );

    mat->m[x][y] = v;
    ESCREVEMEMLOG( (long int) ( &(mat->m[x][y]) ), sizeof(double), mat->id );
}

// Descricao: retorna o elemento (x,y) de mat 
// Entrada: mat, x, y
// Saida: mat[x][y]
double leElemento (mat_tipo *mat, int x, int y) {
    // verifica se x e y sao validos
    erroAssert( (x < 0) || (x >= mat->tamX), "Indice invalido" );
    erroAssert( (y < 0) || (y >= mat->tamY), "Indice invalido" );

    LEMEMLOG( (long int) ( &(mat->m[x][y]) ), sizeof(double), mat->id );
    return mat->m[x][y];
}

// Descricao: faz uma copia de src em dst
// Entrada: src, dst_id
// Saida: dst
void matrizParaTxt(mat_tipo *src) {
    int i,j;

    FILE *matriz;

    matriz = fopen(src->matrixPath, "w");

    // Verificando se a abertura do arquivo ocorreu corretamente
    erroAssert(matriz != NULL, "Ocorreu um erro ao abrir o arquivo.");
    
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
    int i,j;

    // verifica se as dimensoes das matrizes a e b sao as mesmas
    erroAssert(a->tamX == b->tamX, "Dimensoes incompativeis");
    erroAssert(a->tamY == b->tamY, "Dimensoes incompativeis");

    // inicializa a matriz c garantindo a compatibilidade das dimensoes
    criaMatriz(c, a->matrixPath, c->id);
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
    int i,j,k;

    // verifica a compatibilidade das dimensoes 
    erroAssert( a->tamY == b->tamX, "Dimensoes incompativeis" );

    // cria e inicializa a matriz c
    criaMatriz(c, a->matrixPath, c->id);
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

// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
void transpoeMatriz(mat_tipo *a) {
    int i, j, dim;
    
    // determina a maior dimensao entre tamX e tamY
    dim = ( a->tamX > a->tamY ? a->tamX : a->tamY );

    // faz a transposicao como se a matriz fosse quadrada
    for (i = 0; i < dim; i++){
        for(j = i + 1; j < dim; j++){
            ELEMSWAP( (a->m[i][j]), (a->m[j][i]) );
            ESCREVEMEMLOG( (long int) ( &(a->m[i][j]) ), sizeof(double), a->id );
            ESCREVEMEMLOG( (long int) ( &(a->m[j][i]) ), sizeof(double), a->id );
        }
    }

    // inverte as dimensoes da matriz transposta
    ELEMSWAP(a->tamX, a->tamY);
}

// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
void destroiMatriz(mat_tipo *a) {
    // apenas um aviso se a matriz for destruida mais de uma vez
    avisoAssert(( (a->tamX > 0) && (a->tamY > 0) ), "Matriz já foi destruida");

    // torna as dimensoes invalidas
    a->id = a->tamX = a->tamY = -1;
}

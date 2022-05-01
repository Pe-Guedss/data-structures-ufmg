//---------------------------------------------------------------------
// Arquivo	: mat.h
// Conteudo	: definicoes do TAD MAT 
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//---------------------------------------------------------------------

#ifndef MATH
#define MATH

#include "memlog.h"

typedef struct mat{
	double **m;
    char *matrixPath;
    int tamX, tamY;
	int id;
} mat_tipo;

void criaMatrizInput(mat_tipo *mat, char *matrixPath, int id);
void criaMatrizOutput(mat_tipo *mat, char *matrixPath, int tamX, int tamY, int id);
void dimensoesMatriz(mat_tipo *mat);
void inicializaMatrizNula(mat_tipo *mat);
void leMatrizDoTxt(mat_tipo *mat);
double acessaMatriz(mat_tipo *mat);
void imprimeMatriz(mat_tipo *mat);
void matrizParaTxt(mat_tipo *mat);
void escreveElemento(mat_tipo *mat, int x, int y, double v);
double leElemento (mat_tipo *mat, int x, int y);
void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void transpoeMatriz(mat_tipo *a);
void destroiMatriz(mat_tipo *a);

#endif

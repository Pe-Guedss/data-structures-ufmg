//---------------------------------------------------------------------
// Arquivo	: mat.c
// Conteudo	: implementacao do TAD MAT 
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//              : 2021-11-14 - adequacao para versao 1.1 memlog
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x,y) (x+=y,y=x-y,x-=y)

void criaMatriz(mat_tipo * mat, int tx, int ty, int id)
// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty, id
// Saida: mat
{
  // verifica se os valores de tx e ty são validos
  erroAssert(tx>0,"Dimensao nula");
  erroAssert(ty>0,"Dimensao nula");
  erroAssert(tx<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(ty<=MAXTAM,"Dimensao maior que permitido");

  // inicializa as dimensoes da matriz
  mat->tamX = tx;
  mat->tamY = ty;
  // inicializa o identificador da matriz, para rastreamento
  mat->id = id;
}

void inicializaMatrizNula(mat_tipo * mat)
// Descricao: inicializa mat com valores nulos 
// Entrada: mat
// Saida: mat
{
  int i, j;
  // inicializa todos os elementos da matriz com 0, por seguranca 
  for (i=0; i<MAXTAM; i++){
    for(j=0; j<MAXTAM; j++){
      mat->m[i][j] = 0;
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
}

void inicializaMatrizAleatoria(mat_tipo * mat)
// Descricao: inicializa mat com valores aleatorios
// Entrada: mat 
// Saida: mat
{
  int i, j;
  // inicializa a matriz com valores nulos, por seguranca
  inicializaMatrizNula(mat);
  // inicializa a parte alocada da matriz com valores aleatorios
  for (i=0; i<mat->tamX; i++){
    for(j=0; j<mat->tamY; j++){
      mat->m[i][j] = drand48()*INITRANDOMRANGE;
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
}

double acessaMatriz(mat_tipo * mat)
// Descricao: acessa mat para fins de registro de acesso 
// Entrada: mat 
// Saida: mat
{
  int i, j;
  double aux, s=0.0;
  for (i=0; i<mat->tamX; i++){
    for(j=0; j<mat->tamY; j++){
      aux = mat->m[i][j];
      s+=aux;
      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
  return s; // apenas para evitar que acesso seja eliminado
}

void imprimeMatriz(mat_tipo * mat)
// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Entrada: mat
// Saida: impressao na saida padrao (stdout) 
{
  int i,j;

  // seguranca, mas erro não deve acontecer jamais
  erroAssert(mat->tamX<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(mat->tamY<=MAXTAM,"Dimensao maior que permitido");

  // imprime os identificadores de coluna
  printf("%9s"," ");
  for(j=0; j<mat->tamY; j++)
    printf("%8d ",j);
  printf("\n");

  // imprime as linhas
  for (i=0; i<mat->tamX; i++){
    printf("%8d ",i);
    for(j=0; j<mat->tamY; j++){
      printf("%8.2f ",mat->m[i][j]);
      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
    printf("\n");
  }
}

void escreveElemento(mat_tipo * mat, int x, int y, double v)
// Descricao: atribui o valor v ao elemento (x,y) de mat
// Entrada: mat, x, y, v
// Saida: mat
{
  // verifica se x e y sao validos
  erroAssert((x<0)||(x>=mat->tamX),"Indice invalido");
  erroAssert((y<0)||(y>=mat->tamY),"Indice invalido");

  mat->m[x][y] = v;
  ESCREVEMEMLOG((long int)(&(mat->m[x][y])),sizeof(double),mat->id);
}

double leElemento (mat_tipo * mat, int x, int y)
// Descricao: retorna o elemento (x,y) de mat 
// Entrada: mat, x, y
// Saida: mat[x][y] 
{
  // verifica se x e y sao validos
  erroAssert((x<0)||(x>=mat->tamX),"Indice invalido");
  erroAssert((y<0)||(y>=mat->tamY),"Indice invalido");

  LEMEMLOG((long int)(&(mat->m[x][y])),sizeof(double),mat->id);
  return mat->m[x][y];
}

void copiaMatriz(mat_tipo *src, mat_tipo * dst, int dst_id)
// Descricao: faz uma copia de src em dst
// Entrada: src, dst_id
// Saida: dst
{
  int i,j;

  // cria novamente a matriz dst para ajustar as suas dimensoes
  criaMatriz(dst,src->tamX, src->tamY,dst_id);
  // inicializa a matriz dst como nula
  inicializaMatrizNula(dst);
  // copia os elementos da matriz src
  for (i=0; i<src->tamX; i++){
    for(j=0; j<src->tamY; j++){
      dst->m[i][j] = src->m[i][j];
      LEMEMLOG((long int)(&(src->m[i][j])),sizeof(double),src->id);
      ESCREVEMEMLOG((long int)(&(dst->m[i][j])),sizeof(double),dst->id);
    }
  }
}

void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
  int i,j;
  // verifica se as dimensoes das matrizes a e b sao as mesmas
  erroAssert(a->tamX==b->tamX,"Dimensoes incompativeis");
  erroAssert(a->tamY==b->tamY,"Dimensoes incompativeis");

  // inicializa a matriz c garantindo a compatibilidade das dimensoes
  criaMatriz(c,a->tamX, a->tamY, c->id);
  inicializaMatrizNula(c);

  // faz a soma elemento a elemento
  for (i=0; i<a->tamX; i++){
    for(j=0; j<a->tamY; j++){
      c->m[i][j] = a->m[i][j]+b->m[i][j];
      LEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      LEMEMLOG((long int)(&(b->m[i][j])),sizeof(double),b->id);
      ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
    }
  }
}

void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
  int i,j,k;
  // verifica a compatibilidade das dimensoes 
  erroAssert(a->tamY==b->tamX,"Dimensoes incompativeis");

  // cria e inicializa a matriz c
  criaMatriz(c,a->tamX, b->tamY,c->id);
  inicializaMatrizNula(c);

  // realiza a multiplicacao de matrizes
  for (i=0; i<c->tamX;i++){
    for (j=0; j<c->tamY;j++){
      for (k=0; k<a->tamY;k++){
        c->m[i][j] += a->m[i][k]*b->m[k][j];
        LEMEMLOG((long int)(&(a->m[i][k])),sizeof(double),a->id);
        LEMEMLOG((long int)(&(b->m[k][j])),sizeof(double),b->id);
        ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);
      }
    }
  }
}

void transpoeMatriz(mat_tipo *a)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{
  int i,j,dim;
  
  // determina a maior dimensao entre tamX e tamY
  dim = (a->tamX>a->tamY?a->tamX:a->tamY);

  // faz a transposicao como se a matriz fosse quadrada
  for (i=0; i<dim; i++){
    for(j=i+1; j<dim; j++){
      ELEMSWAP((a->m[i][j]),(a->m[j][i]));
      ESCREVEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      ESCREVEMEMLOG((long int)(&(a->m[j][i])),sizeof(double),a->id);
    }
  }
  // inverte as dimensoes da matriz transposta
  ELEMSWAP(a->tamX,a->tamY);
}

void destroiMatriz(mat_tipo *a)
// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
{
  // apenas um aviso se a matriz for destruida mais de uma vez
  avisoAssert(((a->tamX>0)&&(a->tamY>0)),"Matriz já foi destruida");

  // torna as dimensoes invalidas
  a->id = a->tamX = a->tamY = -1;
}

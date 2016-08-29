#include "linearSystemCreator.h"

/***********************
 * N: tamanho do sistema linear
 * k: numero da diagonal, 0 = diagonal principal, 1 = acima/abaixo da diagonal, 2 = ...
 * kMax: numero de bandas do sistema linear
 * diag: vetor para armazenar os valores da diagonal. Deve ser alocado por quem chama a função.
 ***********************/
int generateRandomDiagonal(unsigned int N, unsigned int k, unsigned int kMax, double *diag){
  if ((!diag) || (N < 3) || (kMax > N/2) || (k < 0) || (k > kMax)){
    return (-1);
  }

  /* garante valor dominante para diagonal principal */
  double fator = (k == 0) ? ((double)(kMax-1)) : (0.0);

  double invRandMax = 1.0 / (double)RAND_MAX;

  for (int i=0; i < N-k; ++i){
    diag[i] = fator + (double)rand() * invRandMax;
  }

  return (0);
}

int generateRandomDiagonalMatrix(unsigned int N, unsigned int k, double **A){
  int nDiagonals = (k*2)-1;
  int i;

  if ((!A) || (N < 3) || (k > N/2) || (k < 0)){
    return (-1);
  }

  srand(20162);

  // Aloca matriz
  A = (double**)malloc(sizeof(double*)*nDiagonals);
  for(i=0;i<nDiagonals;++i){
    A[i] = (double*)malloc(sizeof(double)*N);
    // Gera a diagonal randomicamente
    generateRandomDiagonal(N, abs(i-((nDiagonals-1)/2)), k, A[i]);
  }

  return (0);
}

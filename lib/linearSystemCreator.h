#include <stdlib.h>

//=================================================================================================

/***********************
 * N: tamanho do sistema linear
 * k: numero da diagonal, 0 = diagonal principal, 1 = acima/abaixo da diagonal, 2 = ...
 * kMax: numero de bandas do sistema linear
 * diag: vetor para armazenar os valores da diagonal. Deve ser alocado por quem chama a função.
 ***********************/
int generateRandomDiagonal(unsigned int N, unsigned int k, unsigned int kMax, double *diag);

//=================================================================================================

/***********************
 * N: tamanho do sistema linear
 * k: numero de bandas do sistema linear
 * A: matriz para armazenar os valores das diagonais. É alocado na função
 ***********************/
int generateRandomDiagonalMatrix(unsigned int N, unsigned int k, double **A);

//=================================================================================================

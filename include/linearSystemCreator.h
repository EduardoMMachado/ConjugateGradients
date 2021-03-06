// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// =============================================================================
// Parâmetros:
//  N = tamanho do sistema linear
//  k = numero da diagonal, 0 = diagonal principal, 1 = acima/abaixo da diagonal, 2 = ...
//  nBandas = numero de bandas do sistema linear
//  diag = vetor para armazenar os valores da diagonal. Deve ser alocado por quem chama a função.
// =============================================================================
int generateRandomDiagonal(unsigned int N, unsigned int k, unsigned int nBandas, double *diag);


// =============================================================================
// Parâmetros:
//  x = x da função f(x) = (i * M_PI) / n
// =============================================================================
double independentTermGenerator(double x);

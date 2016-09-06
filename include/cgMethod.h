// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

double timestamp(void);

// =============================================================================
//Parametros:
//	A = matriz de coeficientes do sistema linear
//	b = vetor de termos independentes
//	x = vetor soluçao
//	N = numero de dimensoes do sistema
//	maxIter = numero maximo de iteraçoes definido pelo usuario ou o numero de dimensoes do sistema
//	tolerance = o erro aproximado absoluto máximo (se houver)
// 	outFileName = nome do arquivo de saida
// =============================================================================
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int maxIter, unsigned int tolerance, char *outFileName);
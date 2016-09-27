// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

double timestamp(void);

// =============================================================================
// Parametros:
//	r = vetor de resíduos
//  stepSize = tamanho do passo
//  z = A * v
//	N = dimenção do sistema linear
// 	outFileName = nome do arquivo de saida
// =============================================================================
double residueCalculator(double *r, double stepSize, double *z, unsigned int N);

// =============================================================================
// Parametros:
//	r = vetor de resíduos
//	N = dimenção do sistema linear
// 	outFileName = nome do arquivo de saida
// =============================================================================
double normCalculator(double *r, unsigned int N);

// =============================================================================
// Parametros:
//	A = matriz de coeficientes do sistema linear
//	b = vetor de termos independentes
//	x = vetor soluçao
//	N = numero de dimensoes do sistema
//  k = numero de bandas
//	maxIter = numero maximo de iteraçoes definido pelo usuario ou o numero de dimensoes do sistema
//	tolerance = o erro aproximado absoluto máximo (se houver)
// 	outFileName = nome do arquivo de saida
// =============================================================================
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int k, unsigned int maxIter, double tolerance, const char *outFileName);

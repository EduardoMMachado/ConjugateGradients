// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include "cgMethod.h"

// =============================================================================
double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}
// =============================================================================

// =============================================================================
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int maxIter, unsigned int tolerance, char *outFileName){
	unsigned int n_iter = 0;																											// Número de iterações feitas
	double rTimeMin, rTimeMean, rTimeMax, rTimeStart, rTimeEnd, rTime;						// Tempos de resíduo
	double cgTimeMin, cgTimeMean, cgTimeMax, cgTimeStart, cgTimeEnd, cgTime;			// Tempos do cálculo do método
	double stepSize;

	// Aloca vetores de resíduo e norma
	double *r (double*) malloc(N*sizeof(double));
	double *norm (double*) malloc(maxIter*sizeof(double));
	double *error (double*) malloc(maxIter*sizeof(double));

	// Inicializa os resíduos e norma para a iteração 0
	rTimeStart = timestamp();
	residueCalculator(r, A, x, b, N);
	rTimeEnd = timestamp();

	norm[n_iter] = normCalculator(r, N);
	error[n_iter] = norm[n_iter];

	rTimeMin = rTime;
	rTimeMean = rTime;
	tTimeMax = rTime;

	while((n_iter <= maxIter)and(error[i] > tolerance))
	{
		n_iter++;

		// =========================================================================
		// Método
		// =========================================================================




		// =========================================================================

		cgTimeStart = timestamp();

		// Calculo dos resíduos
		rTimeStart = timestamp();
		residueCalculator(r, A, x, b, N);
		rTimeEnd = timestamp();
		// Calculo da norma
		norm[n_iter] = normCalculator(r, N);
		// Calculo do erro
		error[i] = abs(norm[i] - norm[i-1]);

		// Calculo de tempos de execução
		cgTimeEnd = timestamp();

		cgTime = cgTimeEnd - cgTimeStart;
		if(n_iter == 1)
		{
			cgTimeMin = cgTime;
			cgTimeMean = cgTime;
			cgTimeMax = cgTime;
		}
		else
		{
			if(cgTime < cgTimeMin) cgTimeMin = cgTime;
			else if(cgTime > cgTimeMax) cgTimeMax = cgTime;
			cgTimeMean += cgTime;
		}

		rTime = rTimeEnd - rTimeStart;
		if(rTime < rTimeMin) rTimeMin = rTime;
		else if(rTime > rTimeMax) rTimeMax = rTime;
		rTimeMean += rTime;
	}


	return(0);
}
// =============================================================================

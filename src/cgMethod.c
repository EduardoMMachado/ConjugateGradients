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
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int k, unsigned int maxIter, unsigned int tolerance, char *outFileName){
	unsigned int n_iter = 0;																											// Número de iterações feitas
	double rTimeMin, rTimeMean, rTimeMax, rTimeStart, rTimeEnd, rTime;						// Tempos de resíduo
	double cgTimeMin, cgTimeMean, cgTimeMax, cgTimeStart, cgTimeEnd, cgTime;			// Tempos do cálculo do método
	double stepSize;
	int i,j;

	// Aloca vetores de resíduo e norma
	double *r = (double*) malloc(N*sizeof(double));
	double *norm = (double*) malloc(maxIter*sizeof(double));
	double *error = (double*) malloc(maxIter*sizeof(double));

	// Aloca vetores auxiliares do metodo
	double *v = (double*) malloc(N*sizeof(double)); //vetor de direçao
	double *s = (double*) malloc(N*sizeof(double)); //vetor de passos
	double *z = (double*) malloc(N*sizeof(double));
	double *aux = (double*) malloc(N*sizeof(double));

	// Inicializa os resíduos e norma para a iteração 0

	rTimeStart = timestamp();
	residueCalculator(r, A, x, b, N);
	rTimeEnd = timestamp();

	norm[n_iter] = normCalculator(r, N);
	error[n_iter] = norm[n_iter];

	//r=b e v=b
	for (i = 0; i < N; i++)
    v[i] = r[i] = b[i];

	rTimeMin = rTime;
	rTimeMean = rTime;
	tTimeMax = rTime;

	while((n_iter <= maxIter)and(error[i] > tolerance))
	{
		
		cgTimeStart = timestamp();

		// =========================================================================
		// Método
		// =========================================================================

		//z=Av
  	for (i = 0; i < N; i++) {
  		jv = i
    	for (j = 0; j <= k; j++)
    	{
      	z[i] += A[i][j] * v[jv]; //ALTERAR INDICES DE A -> SO TEMOS DIAGONAIS

      	// faz calculo para a parte de baixo da matriz
	    	if(j != 0)
	    	{
	    		z[i] += A[i][j] * v[jv-j];
	    	}

      	jv++;
      }
  	}

  	
  	//s = rt*r/vt*z
  	for (i = 0; i < N; i++){
  		s = (r[i]*r[i]) / v[i] * z[i];
  	}

  	//prox x = x + s*v
  	for (i = 0; i < N; i++) {
  		x[i] = x[i] + s[i]*v[i];
  	}

		// =========================================================================


		// Calculo dos resíduos
		rTimeStart = timestamp();
		//r = r - s*z
		residueCalculator(r, A, x, b, N);
		rTimeEnd = timestamp();
		// Calculo da norma
		norm[n_iter] = normCalculator(r, N);
		// Calculo do erro
		error[i] = abs(norm[i] - norm[i-1]);

		//calcula novo vetor de direçoes
		for (i = 0; i < N; i++)
  		v[i] = r[i] + ( norm[n_iter]/norm[n_iter-1] ) *v[i]; ////// CONFERIR

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

		n_iter++;


	}


	return(0);
}
// =============================================================================

// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include "cgMethod.h"

// =============================================================================
double timestamp(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}
// =============================================================================

int residueCalculator(double *r, double stepSize, double *z, unsigned int N)
{
	for (int i = 0; i<=N ;++i){
		r[i] = r[i] - stepSize*z[i];
	}
	return 0;
}

double normCalculator(double *r, unsigned int N)
{
	double norm =0;

	for (int i = 0; i<=N ;++i){
		norm += r[i] * r[i];
	}
	norm = sqrt(norm);
	return norm;
}

// =============================================================================
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int k, unsigned int maxIter, unsigned int tolerance, const char *outFileName){
	unsigned int n_iter = 0;																											// Número de iterações feitas
	double rTimeMin, rTimeMean, rTimeMax, rTimeStart, rTimeEnd, rTime;						// Tempos de resíduo
	double cgTimeMin, cgTimeMean, cgTimeMax, cgTimeStart, cgTimeEnd, cgTime;			// Tempos do cálculo do método
	double stepSize, aux, aux1, m, vtz;
	int i,j, jv;

	// Aloca vetores de resíduo e norma
	double *r = (double*) malloc(N*sizeof(double));
	double *norm = (double*) malloc(maxIter*sizeof(double));
	double *error = (double*) malloc(maxIter*sizeof(double));

	// Aloca vetores auxiliares do metodo
	double *v = (double*) malloc(N*sizeof(double)); //vetor de direçao
	double *z = (double*) malloc(N*sizeof(double));

	//r=b e v=b
	for (i = 0; i < N; i++)
    	v[i] = r[i] = b[i];

	// aux = rt*r
	aux = 0.0;
	for(i = 0; i < N; ++i){
		aux += r[i]*r[i];
	}

	// Inicializa os resíduos e norma para a iteração 0
	norm[n_iter] = normCalculator(r, N);
	error[n_iter] = norm[n_iter];
	printf("error[n_iter] :%lf\n", error[n_iter]);

	while((n_iter <= maxIter) && (error[n_iter] > tolerance))
	{
		cgTimeStart = timestamp();

		// =========================================================================
		// Método
		// =========================================================================
		//z=Av
	  	for (i = 0; i < N; ++i) {
	  		jv = i;
	    	for (j = 0; j <= k; ++j){
	    		if(jv < N){
		      		z[i] += A[j][i] * v[jv];
			    }
	      		// faz calculo para a parte de baixo da matriz
		    	if(j != 0)
		    	{
		    		z[i] += A[j][i] * v[jv-j];
		    	}
	      		jv++;
	      	}
	  	}
	    // vt*z
	    vtz = 0.0;
	    for(i = 0; i < N; ++i){
	      vtz += v[i]*z[i];
	    }
	  	//s = rt*r/vt*z
	  	stepSize = aux / vtz;
	  	//prox x = x + s*v
	  	for (i = 0; i < N; ++i) {
	  		x[i] = x[i] + stepSize*v[i];
	  	}

		// =========================================================================

		// Calculo dos resíduos
		rTimeStart = timestamp();
		//r = r - s*z
		residueCalculator(r, stepSize, z, N);
		rTimeEnd = timestamp();
	    // aux1 = rt*r
	    aux1 = 0.0;
	    for(i = 0; i < N; ++i){
	      aux1 += r[i]*r[i];
	    }
	    m = aux1 / aux;
	    aux = aux1;
		//calcula novo vetor de direçoes
		for (i = 0; i < N; i++)
  		v[i] = r[i] + (m * v[i]);



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

	    // Calculo da norma
	    norm[n_iter] = normCalculator(r, N);
	    // Calculo do erro
	    error[n_iter] = abs(norm[n_iter] - norm[n_iter-1]);
	}

	//imprime vetor de soluçoes
	for(int i = 0 ; i < N ; ++i){
		printf("%lf\n", x[i]);
	}

	printf("n_iter: %d\n", n_iter);
	return 0;
}
// =============================================================================

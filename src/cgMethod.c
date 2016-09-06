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
	double *r = (double*) malloc(N*sizeof(double));
	double *norm = (double*) malloc(maxIter*sizeof(double));
	double *error = (double*) malloc(maxIter*sizeof(double));

	// Inicializa os resíduos e norma para a iteração 0
	
	rTimeStart = timestamp();
	residueCalculator(r, A, x, b, N);
	rTimeEnd = timestamp();

//============================= ALGORITMO DO LIVRO ===========================================
	double *v = (double*) malloc(N*sizeof(double)); //vetor de direçao
	double *s = (double*) malloc(N*sizeof(double)); //vetor de passos
	double *z = (double*) malloc(N*sizeof(double));	
	double *aux = (double*) malloc(N*sizeof(double));
	int i,j;

	//r=b e v=b
	for (i = 0; i < N; i++)
    	v[i] = r[i] = b[i];

    norm[n_iter] = normCalculator(r, N);
	
    for(n_iter = 0 ; n_iter <= maxIter ; n_iter++){ // COLOCAR SAIDA COM ERRO POR CAUSA DA IMPRESSAO NO ARQ
    	
		//z=Av
		for (i = 0; i < N; i++) {
        	for (j = 0; j < N; j++)
          		z[i] += A[i*N+j] * v[j]; //ALTERAR INDICES DE A -> SO TEMOS DIAGONAIS
      	}

    	//s = NORMA/vt*z
    	for (i = 0; i < N; i++){
    		s = norm[n_iter] / v[i] * z[i];
    	}


    	//prox x = x + s*v
    	for (i = 0; i < N; i++) {
    		x[i] = x[i] + s[i]*v[i];
    	}

    	//calcula o residuo -> r= r - s*z
    	rTimeStart = timestamp();
		residueCalculator(r, s, z);
		rTimeEnd = timestamp();
	  	
	  	norm[n_iter] = normCalculator(r, N);
		error[n_iter] = abs(norm[n_iter] - norm[n_iter-1]);
		
		//se o erro for menor que a tolerancia retorna 0 e a funçao acaba com sucesso, e o vetor x eh a soluçao
		if(error[n_iter] < tolerance)
			return 0;

		//calcula novo vetor de direçoes
		for (i = 0; i < N; i++)
    		v[i] = r[i] + ( norm[n_iter]/norm[n_iter-1] ) *v[i];


    }

   //OBS1: em s onde usa a norma, no livro eh usada uma variavel aux = rt*r
   //OBS2: o calculo da norma no livro eh feita por uma variavel aux1 =rt*r
   //OBS3: o criterio de parada do if de tolerancia eh aux1 e no calculo no novo vetor v de passos no lugar da norma eh usado o m = aux1/aux e o aux recebe o valor de aux 1

 //=============================== FIM ALGORITMO DO LIVRO ==============================================

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

// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include "cgMethod.h"


// =============================================================================
double timestamp()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}
// =============================================================================


// =============================================================================
int residueCalculator(double *r, double stepSize, double *z, unsigned int N)
{
  // Calcula o resíduo de acordo com o passo
	for (int i = 0; i < N ;++i)
  {
		r[i] = r[i] - (stepSize * z[i]);
	}

	return(0);
}
// =============================================================================


// =============================================================================
double normCalculator(double *r, unsigned int N)
{
  // Inicializa a norma
	double norm = 0;

  // Calcula Rt*R
	for (int i = 0; i < N ;++i)
  {
		norm += r[i] * r[i];
	}
  // Calcula a raiz
	norm = sqrt(norm);

	return(norm);
}
// =============================================================================


// =============================================================================
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int k, unsigned int maxIter, unsigned int tolerance, const char *outFileName){
	unsigned int n_iter = 0;																											// Número de iterações feitas
	double rTimeMin, rTimeMean, rTimeMax, rTimeStart, rTimeEnd, rTime;						// Tempos de resíduo
	double cgTimeMin, cgTimeMean, cgTimeMax, cgTimeStart, cgTimeEnd, cgTime;			// Tempos do cálculo do método
	double stepSize, aux, aux1, m, vtz;
	int i, j, jv;
  FILE* outFile;

	// Aloca vetores de resíduo e norma
	double *r = (double*) malloc(N*sizeof(double));
	double *norm = (double*) malloc(maxIter*sizeof(double));
	double *error = (double*) malloc(maxIter*sizeof(double));

	// Aloca vetores auxiliares do metodo
	double *v = (double*) malloc(N*sizeof(double));
	double *z = (double*) malloc(N*sizeof(double));

  // Estabelece
	// R=B
  // V=B
	for (i = 0; i < N; i++)
  {
    v[i] = r[i] = b[i];
  }

  // Calcula
	// aux = Rt * R
	aux = 0.0;
	for(i = 0; i < N; ++i)
  {
		aux += r[i]*r[i];
	}

	// Inicializa os resíduos e norma para a iteração 0
	norm[n_iter] = normCalculator(r, N);
	error[n_iter] = norm[n_iter];

  // Fica no laço enquando o erro é maior que a tolerancia e ainda não foi
  // executado o número máximo de iterações
	while((n_iter < maxIter) && (error[n_iter] > tolerance))
	{
		cgTimeStart = timestamp();

    // Calcula
		// Z = A * V
    memset(z, 0.0, N*sizeof(double));
  	for (i = 0; i < N; ++i)
    {
  		jv = i;
    	for (j = 0; j <= k; ++j)
      {
	      z[i] += A[j][i] * v[jv];

      	// faz calculo para a parte de baixo da matriz
	    	if(((jv-(2*j)) >= 0)&&(jv != i))
	    	{
	    		z[i] += A[j][i-j] * v[jv-(2*j)];
	    	}

      	jv++;
      }
  	}

    // Calcula
    // vtz = Vt * Z
    vtz = 0.0;
    for(i = 0; i < N; ++i)
    {
      vtz += v[i]*z[i];
    }

    // Calcula
  	// s = (Rt * R) / (Vt * Z)
  	stepSize = aux / vtz;

  	//prox X(k+1) = X(k) + s * V
  	for (i = 0; i < N; ++i)
    {
  		x[i] = x[i] + stepSize*v[i];
  	}


		// Calculo dos resíduos
		rTimeStart = timestamp();
		residueCalculator(r, stepSize, z, N);
		rTimeEnd = timestamp();

    // aux1 = Rt * R
    aux1 = 0.0;
    for(i = 0; i < N; ++i)
    {
      aux1 += r[i]*r[i];
    }

    m = aux1 / aux;

    aux = aux1;

    //calcula novo vetor de direçoes
		for (i = 0; i < N; i++)
    {
  		v[i] = r[i] + (m * v[i]);
    }



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

    // Incrementa o número de iterações
		n_iter++;

    // Calculo da norma
    norm[n_iter] = normCalculator(r, N);
    // Calculo do erro
    error[n_iter] = abs(norm[n_iter] - norm[n_iter-1]);
	}

  // Escrita dos resultados no arquivo de saída
  outFile = fopen(outFileName, "w");

  fprintf(outFile, "###########\n");
  fprintf(outFile, "# Tempo Método CG: %lf %lf %lf\n", cgTimeMin, cgTimeMean, cgTimeMax);
  fprintf(outFile, "# Tempo Resíduo: %lf %lf %lf\n", cgTimeMin, cgTimeMean, cgTimeMax);
  fprintf(outFile, "# \n");
  fprintf(outFile, "# Norma Euclidiana do Residuo e Erro aproximado\n");
  for(i = 0; i < n_iter; ++i)
  {
    fprintf(outFile, "# i=%d %lf %lf\n", i, norm[i], error[i]);
  }
  fprintf(outFile, "###########\n");
  fprintf(outFile, "%d\n", N);
  for(i = 0; i < N; ++i)
  {
    fprintf(outFile, "%lf ", x[i]);
  }
  fprintf(outFile, "\n###########\n");


	return(0);
}
// =============================================================================

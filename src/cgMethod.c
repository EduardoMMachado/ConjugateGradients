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
double residueCalculator(double *r, double stepSize, double *z, unsigned int N)
{
	double rTimeStart, rTimeEnd;
	unsigned int i;

	rTimeStart = timestamp();
	// Calcula o resíduo de acordo com o passo
	for (i = 0; i < N ;++i)
	{
		r[i] = r[i] - (stepSize * z[i]);
	}
	rTimeEnd = timestamp();


	return rTimeEnd - rTimeStart;
}
// =============================================================================


// =============================================================================
double normCalculator(double *r, unsigned int N)
{
	// Inicializa a norma
	double norm = 0;
	unsigned int i;

	// Soma a norma atual com Rt*r
	for (i = 0; i < N ;++i)
	{
		norm += r[i] * r[i];
	}
	// Calcula a raiz
	norm = sqrt(norm);

	return(norm);
}
// =============================================================================


// =============================================================================
int conjugateGradients(double **A, double *b, double *x, unsigned int N, unsigned int k, unsigned int maxIter, double tolerance, const char *outFileName){
	unsigned int nIter = 0;																											// Número de iterações feitas
	double rTimeMin, rTimeMean, rTimeMax, rTime;						// Tempos de resíduo
	double cgTimeMin, cgTimeMean, cgTimeMax, cgTimeStart, cgTimeEnd, cgTime;			// Tempos do cálculo do método
	double stepSize, aux, aux1, m, vtz;
	unsigned int i, j, jv, unsignedZero = 0;
	FILE* outFile;

	// Aloca vetores de resíduo e norma
	double *r = (double*) malloc(N*sizeof(double));
	double *norm = (double*) malloc((maxIter+1)*sizeof(double));
	double *error = (double*) malloc((maxIter+1)*sizeof(double));
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
	norm[nIter] = normCalculator(r, N);
	error[nIter] = norm[nIter];

	// Fica no laço enquando o erro é maior que a tolerancia e ainda não foi
	// executado o número máximo de iterações
	while((nIter < maxIter)&&(error[nIter] > tolerance))
	{
		cgTimeStart = timestamp();

		// Calcula
		// Z = A * V
		memset(z, 0.0, N*sizeof(double));
		for (i = 0; i < N; ++i)
		{
			jv = i;
			for (j = 0; j < k; ++j)
			{
				z[i] += A[j][i] * v[jv];
				// faz calculo para a parte de baixo da matriz
				if(((jv-(2*j)) >= unsignedZero)&&(jv != i)&&(i > j))
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
		rTime = residueCalculator(r, stepSize, z, N);

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
		if(nIter == 1)
		{
			rTimeMin = rTime;
			rTimeMean = rTime;
			rTimeMax = rTime;

			cgTimeMin = cgTime;
			cgTimeMean = cgTime;
			cgTimeMax = cgTime;

		}
		else
		{
			if(cgTime < cgTimeMin) cgTimeMin = cgTime;
			else if(cgTime > cgTimeMax) cgTimeMax = cgTime;
			cgTimeMean = (cgTimeMin + cgTimeMax)/2;
		}

		if(rTime < rTimeMin) rTimeMin = rTime;
		else if(rTime > rTimeMax) rTimeMax = rTime;
		rTimeMean = (rTimeMin+rTimeMax)/2;

		// Incrementa o número de iterações
		nIter++;

		if(nIter <= maxIter){
			// Calculo da norma
			norm[nIter] = normCalculator(r, N);

			// Calculo do erro
			error[nIter] = fabs(norm[nIter] - norm[nIter-1]);
		}
	}

	// =========================================
	// Escrita dos resultados no arquivo de saída
	outFile = fopen(outFileName, "w");

	fprintf(outFile, "#####################################################################################################################\n");
	fprintf(outFile, "# Tempo Método CG: %.10lfms %.10lfms %.10lfms\n", cgTimeMin, cgTimeMean, cgTimeMax);
	fprintf(outFile, "# Tempo Resíduo: %.10lfms %.10lfms %.10lfms\n", rTimeMin, rTimeMean, rTimeMax);
	fprintf(outFile, "# \n");
	fprintf(outFile, "# Norma Euclidiana do Residuo e Erro aproximado\n");
	for(i = 1; i <= nIter; ++i)
	{
		if(i < 10) fprintf(outFile, "# i=%d\t%.50lf\t%.50lf\n", i, norm[i], error[i]);
		else fprintf(outFile, "# i=%d\t\t%.50lf\t%.50lf\n", i, norm[i], error[i]);
	}
	fprintf(outFile, "#####################################################################################################################\n");
	fprintf(outFile, "%d\n", N);
	for(i = 0; i < N; ++i)
	{
		fprintf(outFile, "%.14g ", x[i]);
	}
	fprintf(outFile, "\n#####################################################################################################################\n");

	fclose(outFile);
	// =========================================

	// Desaloca vetores de resíduo e norma
	free(r);
	free(norm);
	free(error);
	// Desaloca vetores auxiliares do metodo
	free(v);
	free(z);
	return(0);
}
// =============================================================================

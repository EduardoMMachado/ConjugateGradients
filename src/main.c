// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include "linearSystemCreator.h"
#include "cgMethod.h"

int main(int argc, char const *argv[])
{
	// Variáveis para parâmetros de entrada
	unsigned int n, nBandas, maxIter = 0;
	double tolerance = 0;
	const char *outFileName;
	// Demais variáveis
	unsigned int i;


	// Verifica o número de parâmetros de entrada
	if(argc < 3)
	{
		fprintf(stderr, "Parametros insuficientes.\n");
		fprintf(stderr, "Use:\n");
		fprintf(stderr, "./cgSolver n nBandas -i <maxIter> -t <tolerancia> -o <arquivo_saida>\n\n");
		fprintf(stderr, "n: (n>0) parâmetro obrigatório definindo a dimensão do Sistema Linear.\n");
		fprintf(stderr, "nBandas: parâmetro obrigatório definindo o número de bandas da matriz A.\n");
		fprintf(stderr, "-i maxIter: parâmetro opcional definindo o número máximo de iterações a serem\n            executadas. Caso não seja definido, utilizar o valor n.\n");
		fprintf(stderr, "-t tolerancia: parâmetro opcional definindo o erro aproximado absoluto máximo,\n               considerando a norma Euclidiana do resíduo.\n");
		fprintf(stderr, "-o arquivo_saida: parâmetro obrigatório no qual arquivo_saida é o caminho\n                  completo para o arquivo que vai conter a solução.\n");
		return(-1);
	}


	// Leitura dos parâmetros
	n = atoi(argv[1]);
	nBandas = atoi(argv[2]);
	for(i=3; i<argc; ++i)
	{
		if(strcmp(argv[i], "-i") == 0) maxIter = atoi(argv[i+1]);
		else if(strcmp(argv[i], "-t") == 0) tolerance = atof(argv[i+1]);
		else if(strcmp(argv[i], "-o") == 0) outFileName = argv[i+1];
	}
	if(maxIter == 0) maxIter = n;

	// Validação dos argumentos
	if(n<=0)
	{
		fprintf(stderr, "Dimensão do sistema linear inválido.\n");
		return(-1);
	}
	else if((nBandas<0)||(nBandas > n/2)||(nBandas%2 == 0))
	{
		fprintf(stderr, "Número de bandas inválido.\n");
		return(-1);
	}
	else if(outFileName == NULL)
	{
		fprintf(stderr, "Nome do arquivo de saída inválido.\n");
		return(-1);
	}


	// Inicialiador randomico
	srand(20162);

	// Aloca vetor de termos independentes
	double *b = (double*)malloc(sizeof(double)*n);
	// Aloca vetor de soluções lineares
	double *x = (double*)malloc(sizeof(double)*n);
	// Aloca diagonais
	double **A = (double**)malloc(sizeof(double*)*((nBandas/2)+1));
	for(i = 0; i < ((nBandas/2)+1); ++i)
	{
		A[i] = (double*)malloc(sizeof(double)*n);
		// Preenche as diagonais randomicamente
		generateRandomDiagonal(n, i, nBandas, A[i]);
	}

	// Preenche termos independentes e zera o vetor de soluções (x0)
	for(i=0; i<n; ++i)
	{
		b[i] = independentTermGenerator((i*M_PI)/n);
		x[i] = 0.0;
	}

	// Execução do método
	conjugateGradients(A, b, x, n, (nBandas/2)+1, maxIter, tolerance, outFileName);

	// Desalocação dos vetores e matrizes
	for(i = 0; i < ((nBandas/2)+1); ++i)
	{
			free(A[i]);
	}
	free(A);
	free(b);
	free(x);

	return(0);
}

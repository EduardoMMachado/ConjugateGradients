// Implementado por Eduardo Machado e Bruna Maciel
// 2016

#include "linearSystemCreator.h"

int main(int argc, char const *argv[])
{
  // Variáveis para parâmetros de entrada
  unsigned int n, nBandas, maxIter = 0;
  double tolerance = 0;
  const char *outFileName;
  // Demais variáveis
  unsigned int i, j;

  // Verifica o número de parâmetros de entrada
  if(argc < 3)
  {
      puts("Parametros insuficientes.");
      puts("Use:\n");
      puts("cgSolver n nBandas -i <maxIter> -t <tolerancia> -o <arquivo_saida>\n");
      puts("n: (n>0) parâmetro obrigatório definindo a dimensão do Sistema Linear.\n");
      puts("nBandas: parâmetro obrigatório definindo o número de bandas da matriz A.\n");
      puts("-i maxIter: parâmetro opcional definindo o número máximo de iterações a serem\n            executadas. Caso não seja definido, utilizar o valor n.\n");
      puts("-t tolerancia: parâmetro opcional definindo o erro aproximado absoluto máximo,\n               considerando a norma Euclidiana do resíduo.\n");
      puts("-o arquivo_saida: parâmetro obrigatório no qual arquivo_saida é o caminho\n                  completo para o arquivo que vai conter a solução.\n");
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

  printf("%d - %d - %d - %lf - %s\n", n, nBandas, maxIter, tolerance, outFileName);

  // Validação dos argumentos
  if(n<=0)
  {
    puts("Dimensão do sistema linear inválido.");
    return(-1);
  }
  else if(nBandas<1)
  {
    puts("Número de bandas inválido.");
    return(-1);
  }
  else if(outFileName == NULL)
  {
    puts("Nome do arquivo de saída não encontrado.");
  }

  // Inicialiador randomico
  srand(20162);

  // Aloca vetor de termos independentes
  double *b = (double*)malloc(sizeof(double)*n);
  // Aloca vetor de soluções lineares
  double *x = (double*)malloc(sizeof(double)*n);
  // Preenche termos independentes e zera o vetor de soluções (x0)
  for(i=0; i<n; ++i)
  {
    b[i] = independentTermGenerator((i*M_PI)/n);
    x[i] = 0.0;
  }
  // Aloca diagonais
  double **A = (double**)malloc(sizeof(double*)*nBandas);
  for(i=0; i<nBandas; ++i)
  {
    A[i] = (double*)malloc(sizeof(double)*n);
    // Preenche as diagonais randomicamente
    generateRandomDiagonal(n, i, nBandas, A[i]);
  }

  // ===========================================================================
  // Impressão das diagonais da matriz (Debug)
  for(i=0; i<=nBandas; ++i)
  {
    for(j=0; j<n; ++j)
    {
      printf("%.5lf ", A[i][j]);
    }
    printf("\n");
  }
  for(j=0; j<n; ++j)
  {
    printf("%.5lf ", b[j]);
  }
  printf("\n");
  // ===========================================================================




  return (0);
}

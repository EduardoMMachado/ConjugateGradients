// Implementado por Eduardo Machado
// 2016

#include "linearSystemCreator.h"

int main(int argc, char const *argv[])
{
  unsigned int n, k, maxIter = 0;
  unsigned int i, j;
  double tolerance;
  const char *outFileName;
  FILE* outFile;

  // Verifica o número de parâmetros de entrada
  if(argc < 3)
  {
      puts("Parametros insuficientes.");
      puts("Use:\n");
      puts("cgSolver n k -i <maxIter> -t <tolerancia> -o <arquivo_saida>\n");
      puts("n: (n>0) parâmetro obrigatório definindo a dimensão do Sistema Linear.\n");
      puts("k: parâmetro obrigatório definindo o número de bandas da matriz A.\n   k=0 indica uma matriz diagonal. k=1 é uma matriz tridiagonal.\n   k=2 é uma matriz pentadiagonal, e assim por diante.\n");
      puts("-i maxIter: parâmetro opcional definindo o número máximo de iterações a serem\n            executadas. Caso não seja definido, utilizar o valor n.\n");
      puts("-t tolerancia: parâmetro opcional definindo o erro aproximado absoluto máximo,\n               considerando a norma Euclidiana do resíduo.\n");
      puts("-o arquivo_saida: parâmetro obrigatório no qual arquivo_saida é o caminho\n                  completo para o arquivo que vai conter a solução.\n");
      return(-1);
  }

  // Leitura dos parâmetros
  n = atoi(argv[1]);
  k = atoi(argv[2]);
  for(i=3; i<argc; ++i)
  {
    if(strcmp(argv[i], "-i") == 0) maxIter = atoi(argv[i+1]);
    else if(strcmp(argv[i], "-t") == 0) tolerance = atof(argv[i+1]);
    else if(strcmp(argv[i], "-o") == 0) outFileName = argv[i+1];
  }
  if(maxIter == 0) maxIter = n;

  printf("%d - %d - %d - %lf - %s\n", n, k, maxIter, tolerance, outFileName);

  // Validação dos argumentos
  if(n<=0)
  {
    puts("Dimensão do sistema linear inválido.");
    return(-1);
  }
  else if(k<0)
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

  // Aloca diagonais
  double **A = (double**)malloc(sizeof(double*)*k);
  for(i=0; i<=k; ++i)
  {
    A[i] = (double*)malloc(sizeof(double)*n);
    // Preenche as diagonais randomicamente
    generateRandomDiagonal(n, i, k, A[i]);
  }


  for(i=0; i<=k; ++i)
  {
    for(j=0; j<n; ++j)
    {
      printf("%.5lf ", A[i][j]);
    }
    printf("\n");
  }

  return (0);
}


#----------------------------     Autoria      -------------------------------#
 2016/2

 Bruna de Freitas Maciel	- GRR20130624														
 Eduardo Maia Machado  - GRR20142062	

 Implementaçao do metodo do gradiente conjulgado para soluçao de sistemas 
 lineares da forma Ax = b em que a matriz de coeficientes A, eh matriz de 
 banda, simétrica, definida positiva, e altamente esparsa para o trabalho 1 da 
 disciplina Ci164 - Introduçao a Computaçao Cientifica.
 				  														
#-----------------------------------------------------------------------------#

#--------------------      Arquivos do pacote      ---------------------------#

./bfm13-emm14/: diretório principal;

./bfm13-emm14/src : diretorio com os arquivos .c
	.../src/cgMethod.c : arquivo com as funçoes de implementaçao do metodo do 
						 gradiente conjulgado.
	.../src/linearSystemCreator.c :	arquivo com as funçoes para criaçao do 
									sistema linear (matriz A e o vetor b).
	.../src/main.c

./bfm13-emm14/include :  diretorio com os arquivos .h
	.../include/cgMethod.h
	.../include/linearSystemCreator.h

./bfm13-emm14/lib :  diretorio com os arquivos .a
	.../lib/cgMethod.a
	.../lib/linearSystemCreator.a

./bfm13-emm14/obj :  diretorio com os arquivos .obj
	.../obj/cgMethod.o
	.../obj/linearSystemCreator.o

./bfm13-emm14/LEIAME;

./bfm13-emm14//Makefile;

#-----------------    Algoritmos e estruturas de dados    --------------------#
 																		
	O algoritmo de metodo do gradiente conjulgado escolhido foi o que esta no
livro usado em sala (M. Cristina C. Cunha, Métodos Numéricos), pois foi o que 
tivemos mais facilidade para entender o funcionameto. 
	Os algoritmos de geraçao da matriz A e do vetor b foram dados na 
especificaçao do trabalho.

	A estrutura de dados para A foi uma matriz que armazena apenas a diagonal 
principal e as diagonais superiores do sistema linear, isso pois a matriz eh 
de banda e simetrica, entao os valores fora das diagonais sao sempre zero e as 
diagonais inferiores sao iguais as superiores. Armazenando dessa forma foi 
possivel diminuir o espaço utilizado pela matriz A de n*n para   n * (teto(
nBandas/2)).
	As demais partes do sistema linear (b e x) sao vetores de tamanho n.

 																		
#-----------------------------------------------------------------------------#

#-----------------      Dificuldades na implementaçao     --------------------#
 									
	Os calculos envolvedo a matriz A foi um desafio devido a estrutura de 
dados escolhida, isso ocorreu pois precisavamos duplicar a matriz superior 
para obter a inferior equivalente e tambem evitar que nesses calculos os dados zerados das diagonais fossem acessados.
							
#-----------------------------------------------------------------------------#

#--------------------     Observaçoes Importantes     ------------------------#
 									
	O valor contido na variavel nBandas deve ser o numero de diagonais do 
sistema linear a ser resolvido, por isso esse valor deve ser sempre impar. Na 
implementaçao ´e feita a manipulaçao desse valor para salvarmos apenas as 
diagonais principal e superiores. 
Por exemplo : nBandas = 5, a matriz devera ter 5 diagonais, mas alocamos 
espaço para apenas 3(diagonal principal e as duas superiores).

	A iteraçao 0 eh utilizada apenas para inicializaçao das variaveis 
utilizadas pelo metodo, sendo assim o metodo em si soh eh aplicado a partir da 
iteraçao 1.
							
#-----------------------------------------------------------------------------#

#----------------------      Bugs conhecidos      ----------------------------#
 														  				
	Nenhum bug conhecido.

#-----------------------------------------------------------------------------#


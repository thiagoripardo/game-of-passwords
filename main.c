/* 	
	GRUPO:
		Newton Joaquim Siqueira Neto - 362981
		Thiago Mendes Ripardo Aguiar - 362987
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "./JogoSenha.h"
#include "./cores.h"

/* Bem-vindo! 

(*As informacoes sobre as funcoes utilizadas se encontram no arquivo JogoSenha.c*)

Aqui no main.c encontramos a parte que vai lidar com as entradas das jogadas, as entradas logicas em pequenos menus, como: "opcao", "opcao2" e "retorno". Encontramos tambem a variavel "R", que lida com o retorno da função comparar e a variavel "obter" com o retorno da funcao obter. Nota-se também a utilização de alocação dinamica nos ponteiros "buffer" e "cores" que são responsáveis pela entrada do usuario e as cores geradas pelo computador, respectivamente. */

int main(int narg, char *argv[]) {
	char *buffer, *cores;
	lista *l;
	int PC, N, Lim, opcao, opcao2, obter, retorno=0, tentativas=0, R;

	randomize();

	do {	
		system("clear");
		opcao = Menu();
		inicializar(&l);

		if(opcao == 1) {
			system("clear");
			do{
				printf("\nEntre com o tamanho da senha %s(De 4 a 12 elementos)%s:\n", COR_CIANO, COR_NORMAL);
				scanf("%d", &N);
				descarregar();
			}
			while((N<4)||(N>12));

			do{
				printf("\nEntre com o a possibilidade de cores %s(De 3 a 6)%s:\n", COR_CIANO, COR_NORMAL);
				scanf("%d", &PC);
				descarregar();
			}
			while((PC<3)||(PC>6));

			do{
				printf("\nEntre com o limite de tentativas de advinhação %s(A partir de 1)%s:\n", COR_CIANO, COR_NORMAL);
				scanf("%d", &Lim);
				descarregar();
			}
			while(Lim<1);
			cores=(char*)malloc((3*N+1)*sizeof(char));
			cores = gerar_seq_cores(PC, N);
			system("clear");
			do{
				do{
					if((tentativas == 0) ||	(obter == falso)){
						system("clear");
						printf ("\nEntre uma combinação de %d elementos com %d cores entre as cores a seguir:\n", N, PC);
						Menu_Cores(PC);
					}
					buffer=(char*)malloc((4*N)*sizeof(char));
					fgets(buffer, (4*N), stdin);
					buffer[strlen(buffer)-1] = '\0';
				}
				while(((unsigned)strlen(buffer)<3*N) || ((unsigned)strlen(buffer)>4*N));
				obter = obter_senha(l, regular(buffer, N), N);
				
				
				if(obter == verdadeiro){
					armazenar(&l, regular(buffer, N), cores, N);
					tentativas++;
					R = comparar(l, PC, N, tentativas, Lim);
				}
				else{	
					system("clear");
					printf("\n%sINVALIDO! %s(Você já tentou esta combinação antes!)\n",COR_VERMELHO, COR_NORMAL);
					printf("\n%sPressione:\n(1) - Para inserir uma nova jogada\n(2) - Para retornar ao Menu Principal\nEntre sua opcao:",COR_NORMAL);
					scanf("%d", &retorno);
					descarregar();
					system("clear");
					if(retorno==2)
						Lim = tentativas;
				}
			}
			while((Lim > tentativas) && (R == 0));
		}
		free(l);
		free(buffer);
		free(cores);
		tentativas = 0;
		if(opcao == 2)
			return EXIT_SUCCESS;
		if(retorno !=2 ){
			do{
				printf("\n%sPressione:\n(1) - Para retornar ao Menu Principal\n(2) - Para Sair do programa\nEntre sua opcao:",COR_NORMAL);
				scanf("%d", &opcao2);
			}
			while(opcao2<1 || opcao2>2);
			if(opcao2 == 2)
				opcao=2;
		}
		
	}
	while ((opcao != 2));
	
	

	return EXIT_SUCCESS;
}

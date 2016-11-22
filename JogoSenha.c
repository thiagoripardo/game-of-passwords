/* 	
	GRUPO:
		Newton Joaquim Siqueira Neto - 362981
		Thiago Mendes Ripardo Aguiar - 362987
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./JogoSenha.h"
#include "./cores.h"

/* Bem-vindo! 
O nosso programa de mastermind eh baseado em listas simplesmente encadeadas. Ele utiliza-se de três listas, uma principal nos quais são armazenados os dados de uma rodada e duas listas secundarias que são resetadas no final de cada jogada. As listas secundarias serão utilizadas na função de comparação(comparar), elas são listas temporarias, pois são desalocadas a cada fim de uma jogada. */

//Funcoes descarregar e de menus.

void descarregar(){
	char ch;

	ch = getchar();
	while (ch != '\n' && ch != EOF)
		ch = getchar();
}

int Menu(){
	int op;

	do {	
		printf("\n%so       o%s o o o o o%s o o o o o%s o o o o o%s o o o o o%s o o o o o%s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\n%so o   o o%s o       o%s o        %s     o    %s o        %s o       o%s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\n%so   o   o%s o o o o o%s o o o o o%s     o    %s o o o o o%s o o o o o%s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\n%so       o%s o       o%s         o%s     o    %s o        %s o     o  %s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\n%so       o%s o       o%s o o o o o%s     o    %s o o o o o%s o       o%s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\n");
		printf("\n         %s o       o%s o o o o o%s o       o%s o o o    %s          ", COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_NORMAL);
		printf("\n         %s o o   o o%s     o    %s o o     o%s o     o  %s          ", COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_NORMAL);
		printf("\n         %s o   o   o%s     o    %s o   o   o%s o       o%s          ", COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_NORMAL);
		printf("\n         %s o       o%s     o    %s o     o o%s o     o  %s          ", COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_NORMAL);
		printf("\n         %s o       o%s o o o o o%s o       o%s o o o    %s          ", COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_NORMAL);
		printf("\n");
		printf("\n%so o o o o%s o o o o o%s o o o o o%s o o o o o%s o o o o o%s o o o o o%s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\no			          			  o");
		printf("\no			 Pressione: 			  o\no			          			  o\no			 %s(1) Jogar %s 			  o\no			 %s(2) Sair  %s 			  o\no			          			  o\n", FUNDO_VERMELHO, FUNDO_NORMAL, FUNDO_PRETO, FUNDO_NORMAL);
		
		printf("%so o o o o%s o o o o o%s o o o o o%s o o o o o%s o o o o o%s o o o o o%s", COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO, COR_NORMAL);
		printf("\n");
		printf("\n 			Entre sua opcao: ");
		scanf("%d", &op);
		descarregar();
	} while(op != 1 && op != 2 && op != 3  && op != 4);
	return op;
}

void Menu_Cores(int PC){
	if (PC == 3)
		printf ("\n%s- vm: vermelho\n%s- vd: verde\n%s- am: amarelo\n",COR_VERMELHO, COR_VERDE, COR_AMARELO);
	if (PC == 4)
		printf ("\n%s- vm: vermelho\n%s- vd: verde\n%s- am: amarelo\n%s- az: azul\n",COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL);
	if (PC == 5)
		printf ("\n%s- vm: vermelho\n%s- vd: verde\n%s- am: amarelo\n%s- az: azul\n%s- mg: magenta\n",COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA);
	if (PC == 6)
		printf ("\n%s- vm: vermelho\n%s- vd: verde\n%s- am: amarelo\n%s- az: azul\n%s- mg: magenta\n%s- cn: ciano\n",COR_VERMELHO, COR_VERDE, COR_AMARELO, COR_AZUL, COR_MAGENTA, COR_CIANO);
	printf("\n%sEntre com as cores:\n", COR_NORMAL);
}
/*---------------------------------------------------------------------------------------------------------------------------------------*/

//Funcao para alimentar a semente do rand.

void randomize(){
	srand((unsigned)time( NULL));
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

//Funcoes de inicializacao das estruturas

void inicializar(lista **l){
	(*l) = NULL;
}

void inicializar_sec(lista_secundaria **l){
	(*l) = NULL;
}

void inicializar_sec_2(lista_secundaria_2 **l){
	(*l) = NULL;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

/* Funcoes de armazenar em listas encadeadas, são três: a principal(armazenar) e outras duas secundarias(armazenar_sec_1 e armazenar_sec_2). Todas com alocações dinamicas a depender do tamanho da senha entrado pelo jogador. */

void armazenar(lista **l, char *nome1, char *nome2, int N){
	lista *aux, *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->senha = (char*)malloc((3*N+1)*sizeof(char));
	novo->cores = (char*)malloc((3*N+1)*sizeof(char));
	novo->prox = NULL;

	strcpy(novo->senha, nome1);
	strcpy(novo->cores, nome2);

	if ((*l) == NULL)
		(*l) = novo;
	else{
		aux = (*l);
		while (aux->prox != NULL) 
			aux = aux->prox;
		aux->prox = novo;
	}
}

/* Nas funcoes de armazenar temporarias encontramos o tipo e o cmp(*ver no comentario da funcao comparar, onde sao utilizados*). O tipo funciona como uma chave, no qual a raiz recebe 0, o nó seguinte 1 e assim por diante, já o cmp é um parametro utilizado para a logica de comparação, recebendo 0 inicialmente. */

void armazenar_sec_1(lista_secundaria **l, char *nome1){
	lista_secundaria *aux, *novo;
	int c=1;
	novo = (lista_secundaria *)malloc(sizeof(lista_secundaria));
	novo->senha = (char*)malloc((3)*sizeof(char));
	novo->tipo = 0;
	novo->cmp = 0;
	novo->prox = NULL;
	strcpy(novo->senha, nome1);
	

	if ((*l) == NULL){
		(*l) = novo;
	}
	else{
		aux = (*l);
		while (aux->prox != NULL){
			aux = aux->prox;
			c++;
		}
		novo->tipo = c;
		aux->prox = novo;
	}
}

void armazenar_sec_2(lista_secundaria_2 **l, char *nome1){
	lista_secundaria_2 *aux, *novo;
	int c=1;
	novo = (lista_secundaria_2 *)malloc(sizeof(lista_secundaria_2));
	novo->cores = (char*)malloc((3)*sizeof(char));
	novo->tipo = 0;
	novo->cmp = 0;
	novo->prox = NULL;
	strcpy(novo->cores, nome1);
	

	if ((*l) == NULL){
		(*l) = novo;
	}
	else{
		aux = (*l);
		while (aux->prox != NULL){
			aux = aux->prox;
			c++;
		}
		novo->tipo = c;
		aux->prox = novo;
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

// Funcao que verifica se uma senha ja foi entrada anteriormente na mesma rodada.

int obter_senha(lista *l, char *nome, int N){
	lista *aux;
	aux = (l);
	if (aux == NULL)
		return verdadeiro;
	else{
		while ((aux != NULL) && (strcmp(aux->senha, nome)!=0))
			aux = aux->prox;
	}
	if((aux != NULL)&&(strcmp(aux->senha,nome)==0))
		return falso;
	else
		return verdadeiro;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

/* Funcao que regula a entrada do jogador, eliminando os espaçamentos. Para um melhor armazenamento e posteriormente comparação entre as jogadas inseridas. */

char *regular(char *nome1, int N){
	char *sequencia, *nome, *nome2;
	nome = (char*)malloc((3)*sizeof(char));
	sequencia = (char*)malloc((4*N)*sizeof(char));
	nome2 = (char*)malloc((4*N)*sizeof(char));
	strcpy(nome2,nome1);
	nome = strtok(nome2, ", ");
	
	strcpy(sequencia, nome);

	while(nome != NULL){
		nome = strtok(NULL, ", ");
		if(nome != NULL){
			strcat(sequencia, ",");
			strcat(sequencia, nome);
		}
	}
	free(nome);
	free(nome2);
	return sequencia;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

// Funcoes geradoras

// Funcao que gera numeros pseudo-aleatorios de 1 até o numero entrado, que no caso será estipulado entre 3 e 6.

int gerar(int x){
	int aleatorio;
	aleatorio = 1 + rand()%x;
	return aleatorio;
}

// Funcao que gera uma string de uma cor, utilizando a funcao gerar.

char *gerar_cor(int x){
	char *cor;
	cor=(char*)malloc((3)*sizeof(char));
	if(x==1)
		strcpy(cor, "vm");
	if(x==2)
		strcpy(cor, "vd");
	if(x==3)
		strcpy(cor, "am");
	if(x==4)
		strcpy(cor, "az");
	if(x==5)
		strcpy(cor, "mg");
	if(x==6)
		strcpy(cor, "ci");
	return cor;
}

/* Funcao que gera uma "sequencia de strings", pois a partir da funcao gerar_cor esta funcao agrupa as strings em uma. Fazendo com que o computador jogue uma sequencia, assim como a entrada pelo usuário. */

char *gerar_seq_cores(int PC, int N){
	int aux, i;
	char *sequencia;
	sequencia=(char*)malloc((4*N-1)*sizeof(char));
	aux=gerar(PC);
	strcpy(sequencia, gerar_cor(aux));
	for(i=1;i<N;i++){
		aux=gerar(PC);
		strcat(sequencia, ",");
		strcat(sequencia, gerar_cor(aux));
	}
	return sequencia;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

/* Funcao de comparar, esta funcao compara sequencias de caracteres. Ela funciona da seguinte maneira: é extraido da lista principal a ultima jogada entrada pelo usuario e da mesma forma é extraida a sequencia gerada pelo computador. Ambas as sequencias são quebradas em strings menores que representam as cores, ao mesmo tempo essas strings menores sao armazenadas nas listas temporarias. Logo em seguida, as listas temporarias sao comparadas, determinando se o usuario acertou ou nao e apresentando se acertou no mesmo lugar ou em lugares diferentes. Na logica de comparação que nós pensamos, adicionamos nas listas o "cmp", que é usado para determinar se aquele caractere deve ou nao ser comparado com outros. Pois, se um caractere já foi comparado, ele nao deve ser novamente, marcando assim o cmp como 1.Por fim, a funcao retorna um inteiro indicando se o jogador acertou ou nao as cores. */

int comparar(lista *l, int PC, int N, int T, int Lim){
	lista *aux;
	lista_secundaria *l2, *aux2;
	lista_secundaria_2 *l3, *aux3;
	int i,cp=0,cf=0, c=0;
	char *nome_senha, *nome_cor, *senha, *cores;

	inicializar_sec(&l2);
	inicializar_sec_2(&l3);
	aux = (l);

	nome_senha = (char*)malloc((3)*sizeof(char));
	nome_cor = (char*)malloc((3)*sizeof(char));
	senha = (char*)malloc((3*N + 1)*sizeof(char));
	cores = (char*)malloc((3*N + 1)*sizeof(char));

	while(aux->prox != NULL)
		aux = aux->prox;

	strcpy(senha, aux->senha);
	nome_senha = strtok(senha, " , ");
	armazenar_sec_1(&l2, nome_senha);
	printf("\n");
	while(nome_senha != NULL){
		if(strcmp(nome_senha, "vm")==0)
			printf("%so %s", COR_VERMELHO, COR_NORMAL);
		if(strcmp(nome_senha, "vd")==0)
			printf("%so %s", COR_VERDE, COR_NORMAL);
		if(strcmp(nome_senha, "am")==0)
			printf("%so %s", COR_AMARELO, COR_NORMAL);
		if(strcmp(nome_senha, "az")==0)
			printf("%so %s", COR_AZUL, COR_NORMAL);
		if(strcmp(nome_senha, "mg")==0)
			printf("%so %s", COR_MAGENTA, COR_NORMAL);
		if(strcmp(nome_senha, "ci")==0)
			printf("%so %s", COR_CIANO, COR_NORMAL);
		nome_senha = strtok(NULL, " , ");
		if(nome_senha != NULL){
			armazenar_sec_1(&l2, nome_senha);
		}
	}
	
	strcpy(cores, aux->cores);
	nome_cor = strtok(cores, " , ");
	armazenar_sec_2(&l3, nome_cor);
	
	while(nome_cor != NULL){
		nome_cor = strtok(NULL, " , ");
		if(nome_cor != NULL){
			armazenar_sec_2(&l3, nome_cor);
		}
	}

	aux2 = (l2);
	aux3 = (l3);
	
	while ((aux2 != NULL)){
		if(strcmp(aux2->senha, aux3->cores) == 0){
				aux3->cmp = 1;
				aux2->cmp = 1;
		}
		aux2 = aux2->prox;
		aux3 = aux3->prox;
	}

	aux2 = (l2);
	printf(" -> ");

	while ((aux2 != NULL)){
		aux3 = (l3);
		while((aux3 != NULL)){
			
			if((strcmp(aux2->senha, aux3->cores) == 0) && (aux2->tipo != aux3->tipo) && (aux3->cmp == 0) && (aux2->cmp == 0)){
				printf("!");
				aux3->cmp = 1;
				aux2->cmp = 1;
			}
			
			aux3 = aux3->prox;
		}
		aux2 = aux2->prox;
	}
	
	aux2 = (l2);
	aux3 = (l3);
	
	while ((aux2 != NULL)){
		if(strcmp(aux2->senha, aux3->cores) == 0){
			printf("@");
			c++;
		}
		aux2 = aux2->prox;
		aux3 = aux3->prox;
	}
	
	free(l2);
	free(l3);
	free(nome_senha);
	free(nome_cor);
	free(senha);
	free(cores);
	printf("\n");
	if(c == N){
		printf("\nParabéns! Você conseguiu adivinhar a senha com %d tentativas.\n", T);
		return 1;
	}
	else{
		if(T<Lim)
			printf("\nEsta foi a tentativa de numero %d. Voce nao acertou. Entre sua nova tentativa:\n", T);
		else
			printf("\nEsta foi a tentativa de numero %d. Voce nao acertou.\n", T);
		return 0;
	}
}
		
/*---------------------------------------------------------------------------------------------------------------------------------------*/


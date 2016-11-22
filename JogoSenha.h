/* 	
	GRUPO:
		Newton Joaquim Siqueira Neto - 362981
		Thiago Mendes Ripardo Aguiar - 362987
*/

/* A explanação sobre as estruturas e funcoes se encontra no arquivo JogoSenha.c */

// Variaveis logicas

#define verdadeiro 1
#define falso 0

// Estruturas

typedef struct lista {
	char *senha;
	char *cores;
	struct lista *prox;
} lista;

typedef struct lista_secundaria {
	char *senha;
	int tipo;
	int cmp;
	struct lista_secundaria *prox;
} lista_secundaria;

typedef struct lista_secundaria_2 {
	char *cores;
	int tipo;
	int cmp;
	struct lista_secundaria_2 *prox;
} lista_secundaria_2;

/*---------------------------------------------------------------------------------------------------------------------------------------*/

//Declaração de funcoes 

void descarregar();
int Menu();
void Menu_Cores(int);
void randomize();
void inicializar(lista **);
void inicializar_sec(lista_secundaria **);
void inicializar_sec_2(lista_secundaria_2 **);
void armazenar(lista **, char*, char*, int N);
void armazenar_sec_1(lista_secundaria **, char*);
void armazenar_sec_2(lista_secundaria_2 **, char*);
int obter_senha(lista *, char*, int);
char *regular(char *, int);
int gerar(int);
char *gerar_cor(int);
char *gerar_seq_cores(int, int);
int comparar(lista *, int, int, int, int);

/*---------------------------------------------------------------------------------------------------------------------------------------*/


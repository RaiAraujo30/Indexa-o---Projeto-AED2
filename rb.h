#ifndef RB_H
#define RB_H

#include "aluno.h"

typedef struct tabela tabela;


typedef struct indice_rb {
	int media;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_rb;


enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct no_rb {
	tipo_rb *dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
}no_rb;

typedef no_rb * arvore_rb;

void inicializar_rb(arvore_rb *raiz);
void salvar_arquivo_rb(char *nome, arvore_rb a);
void salvar_auxiliar_rb(arvore_rb raiz, FILE *arq);
arvore_rb carregar_arquivo_rb(char *nome, arvore_rb a);

void adicionar_rb (tipo_rb *valor, arvore_rb *raiz);
void remover_rb (int valor, arvore_rb *raiz);

int altura_rb(arvore_rb raiz);
int maior_rb(int a, int b);
int maior_elemento_rb(arvore_rb raiz);
int menor_elemento_rb(arvore_rb raiz);
void in_order_rb(arvore_rb raiz, tabela *tab);

void imprimir_elemento_rb(arvore_rb raiz, tabela * tab);


void ajustar_rb(arvore_rb *raiz, arvore_rb elemento);
void reajustar_rb(arvore_rb *raiz, arvore_rb elemento);
void rotacao_simples_direita_rb(arvore_rb *raiz, arvore_rb pivo);
void rotacao_simples_esquerda_rb(arvore_rb *raiz, arvore_rb pivo);
void rotacao_dupla_direita_rb(arvore_rb *raiz, arvore_rb pivo);
void rotacao_dupla_esquerda_rb(arvore_rb *raiz, arvore_rb pivo);
void recolorir(arvore_rb pivo);

enum cor cor(arvore_rb elemento);
int eh_raiz(arvore_rb elemento);
int eh_filho_esquerdo(arvore_rb elemento);
arvore_rb irmao(arvore_rb elemento);
arvore_rb tio(arvore_rb elemento);
arvore_rb avo(arvore_rb elemento);
void retira_duplo_preto(arvore_rb *raiz, arvore_rb elemento);


#endif

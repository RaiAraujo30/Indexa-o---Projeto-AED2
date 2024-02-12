#ifndef BST_H
#define BST_H

#include "aluno.h"

typedef struct tabela tabela;

typedef struct structIndiceBst {
	int matricula;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_bst;



typedef struct no_bst {
	tipo_bst *dado;
	struct no_bst *esq, *dir;
} no_bst;

typedef no_bst * arvore_bst;


int inicializarTabela(tabela *tab);
void inicializar_bst(arvore_bst *raiz);
arvore_bst adicionar (tipo_bst *valor, arvore_bst raiz);
int altura_bst(arvore_bst raiz);
tipo_bst * maior_elemento(arvore_bst raiz);
tipo_bst * menor_elemento(arvore_bst raiz);
void pre_order(arvore_bst raiz, tabela *tab);
void pos_order(arvore_bst raiz, tabela *tab);
void in_order(arvore_bst raiz, tabela *tab);
arvore_bst remover_bst(arvore_bst raiz, int matricula);
void imprimir_elemento(arvore_bst raiz, tabela * tab);
void tirar_enter(char *string);

dado * ler_dados();
arvore_bst buscar_bst(arvore_bst raiz, int matricula);
void adicionarAluno(tabela *tab, dado *aluno);
void salvar_arquivo(char *nome, arvore_bst a);
void salvar_auxiliar(arvore_bst raiz, FILE *arq);
arvore_bst procuraMaiorEsquerda(arvore_bst raiz);
arvore_bst carregar_arquivo(char *nome, arvore_bst a);
void finalizar (tabela *tab);

#endif

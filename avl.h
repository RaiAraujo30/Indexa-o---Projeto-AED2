#ifndef AVL_H
#define AVL_H

#include "aluno.h"

typedef struct tabela tabela;

typedef struct indice_avl {
	int idade;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_avl;


typedef struct no {
    int valor;
    tipo_avl *dado;
    int fb;
    int inidice;
    struct no* esq, *dir;
} no;

typedef no* arvoreAVL;

arvoreAVL inserir_avl(arvoreAVL raiz,tipo_avl *valor ,int *cresceu);
void inicializar_avl(arvoreAVL *raiz);
void pre_order_Avl(arvoreAVL raiz);
void in_order_Avl(arvoreAVL raiz, tabela *tab);
void pos_order_Avl(arvoreAVL raiz);
int somatorio_Avl(arvoreAVL raiz);
arvoreAVL busca_Avl(int valor, arvoreAVL raiz);
void dobrar_Avl(arvoreAVL raiz);
void exibir_reverso_Avl(arvoreAVL raiz);
int qtd_par_Avl(arvoreAVL raiz);
int somatorio_par_Avl(arvoreAVL raiz);
int pai_Avl(arvoreAVL raiz, int i);
arvoreAVL podar_Avl(arvoreAVL raiz, int i);
int altura_Avl(arvoreAVL raiz);
arvoreAVL descendentes_Avl(int valor, arvoreAVL raiz);
arvoreAVL remover_avl(arvoreAVL raiz, int indice, int *decresceu);

arvoreAVL buscaPorIdade(arvoreAVL raiz, int idade);
void imprimir_elemento_avl(arvoreAVL raiz, tabela *tab);
void adicionarAlunoAvl(tabela *tab, dado *aluno);
void salvar_arquivoAvl(char *nome, arvoreAVL a);
int inicializarTabelaAvl(tabela *tab);
dado *ler_dados_avl();
arvoreAVL carregar_arquivoAvl(char *nome, arvoreAVL a);
void finalizar_avl(tabela *tab);

#endif

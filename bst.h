#ifndef BST_H
#define BST_H

typedef struct tabela tabela;


typedef struct indice {
	char *chave_nome;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_dado;

typedef struct aluno {
    char nome[81];
    char curso[50];
    int matricula;
    int idade;
    float media;
} dado;

typedef struct no_bst {
	tipo_dado *dado;
	struct no_bst *esq, *dir;
} no_bst;

typedef no_bst * arvore_bst;


void inicializar_bst(arvore_bst *raiz);
arvore_bst adicionar (tipo_dado *valor, arvore_bst raiz);
int altura(arvore_bst raiz);
int maior(int a, int b);
tipo_dado * maior_elemento(arvore_bst raiz);
tipo_dado * menor_elemento(arvore_bst raiz);
void pre_order(arvore_bst raiz, tabela *tab);
void pos_order(arvore_bst raiz, tabela *tab);
void in_order(arvore_bst raiz, tabela *tab);
arvore_bst remover_bst(char *valor, arvore_bst raiz);
void imprimir_elemento(arvore_bst raiz, tabela * tab);
void tirar_enter(char *string);

dado * ler_dados();
void adicionarAluno(tabela *tab, dado *aluno);
void salvar_arquivo(char *nome, arvore_bst a);
void salvar_auxiliar(arvore_bst raiz, FILE *arq);
arvore_bst carregar_arquivo(char *nome, arvore_bst *a);


#endif

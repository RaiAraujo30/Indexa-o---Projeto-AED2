#ifndef BST_H
#define BST_H

typedef struct tabela tabela;

typedef struct indice {
	int chave;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_dado;

typedef struct aluno {
    char nome[3];
    char curso[3];
    int matricula;
    int idade;
    float media;
} dado;

typedef struct no {
    int valor;
    tipo_dado *dado;
    int fb;
    int inidice;
    struct no* esq, *dir;
} no;

typedef no* arvoreAVL;

arvoreAVL inserir_avl(arvoreAVL raiz, int valor, int *cresceu);
void pre_order_Avl(arvoreAVL raiz);
void in_order_Avl(arvoreAVL raiz);
void pos_order_Avl(arvoreAVL raiz);
int somatorio_Avl(arvoreAVL raiz);
arvoreAVL busca_Avl(int valor, arvoreAVL raiz);
void dobrar_Avl(arvoreAVL raiz);
void exibir_reverso_Avl(arvoreAVL raiz);
int qtd_par_Avl(arvoreAVL raiz);
int somatorio_par_Avl(arvoreAVL raiz);
int pai_Avl(arvoreAVL raiz, int i);
arvoreAVL podar_Avl(arvoreAVL raiz, int i);
int altura(arvoreAVL raiz);
arvoreAVL descendentes_Avl(int valor, arvoreAVL raiz);
arvoreAVL remover_Avl(arvoreAVL raiz, int valor);


#endif

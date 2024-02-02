// #ifndef RB_H
// #define RB_H

// typedef struct aluno {
//     char nome[81];
//     char curso[50];
//     int matricula;
//     int idade;
//     float media;
// } dado;

// typedef struct indice {
// 	int chave;
// 	int indice; //posição no arquivo do primeiro byte do registro
// } tipo_dado;


// enum cor { VERMELHO, PRETO, DUPLO_PRETO };

// typedef int tipo_dado;

// typedef struct no_bst {
// 	tipo_dado dado;
// 	enum cor cor;
// 	struct no_bst *esq, *dir, *pai;
// } no_bst;

// typedef no_bst * arvore_rb;

// void inicializar_rb(arvore_rb *raiz);
// void adicionar_rb (int valor, arvore_rb *raiz);
// void remover_rb (int valor, arvore_rb *raiz);

// int altura_rb(arvore_rb raiz);
// int maior_rb(int a, int b);
// int maior_elemento_rb(arvore_rb raiz);
// int menor_elemento_rb(arvore_rb raiz);
// void pre_order_rb(arvore_rb raiz);
// void pos_order_rb(arvore_rb raiz);
// void in_order_rb(arvore_rb raiz);

// void imprimir_elemento_rb(arvore_rb raiz);
// void imprimir_rb(arvore_rb raiz);


// void ajustar_rb(arvore_rb *raiz, arvore_rb elemento);
// void reajustar_rb(arvore_rb *raiz, arvore_rb elemento);
// void rotacao_simples_direita_rb(arvore_rb *raiz, arvore_rb pivo);
// void rotacao_simples_esquerda_rb(arvore_rb *raiz, arvore_rb pivo);


// enum cor cor(arvore_rb elemento);
// int eh_raiz(arvore_rb elemento);
// int eh_filho_esquerdo(arvore_rb elemento);
// arvore_rb irmao(arvore_rb elemento);
// arvore_rb tio(arvore_rb elemento);
// void retira_duplo_preto(arvore_rb *raiz, arvore_rb elemento);


// #endif

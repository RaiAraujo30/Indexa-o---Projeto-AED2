// #include <stdio.h>
// #include <stdlib.h>
// #include "avl.h"
// #include <string.h>

// void inicializar(arvore_avl *raiz) {
// 	*raiz = NULL;
// }

// int inicializarTabela(tabela *tab) {
// 	inicializar(&tab->indice_avl);	
// 	tab->arquivo_dados = fopen("dados.dat", "a+b");
// 	tab->indice_avl = carregar_arquivo("indice_avl.dat", tab->indice_avl);
// 	if(tab->arquivo_dados != NULL)
// 		return 1;
// 	else
//         return 0;
// }

// void finalizar (tabela *tab) {
// 	fclose(tab->arquivo_dados);
// 	salvar_arquivo("indice_avl.dat", tab->indice_avl);
// }

// arvore_avl rotacao_simples_esquerda(arvore_avl pivo) {
//     //inicialização
//     arvore_avl u, t1, t2, t3;
//     u = pivo->dir;
//     t1 = pivo->esq;
//     t2 = u->esq;
//     t3 = u->dir;


//     //Atualização dos ponteiros
//     u->esq = pivo;
//     pivo->dir = t2;

//     return u;

// }

// arvore_avl rotacao_simples_direita(arvore_avl pivo){
//     arvore_avl u, t1, t2, t3;
//     u = pivo->esq;
//     t3 = pivo->dir;
//     t1 = u->esq;
//     t2 = u->dir;

//     //Atualizando os ponteiros
//     u->dir = pivo;
//     pivo->esq = t2;

//     return u;
// }

// arvore_avl rotacao_dupla_direita(arvore_avl pivo) {
//     pivo->esq = rotacao_simples_esquerda(pivo->esq);
//     return rotacao_simples_direita(pivo);
// }

// arvore_avl rotacao_dupla_esquerda(arvore_avl pivo) {
//     pivo->dir = rotacao_simples_direita(pivo->dir);
//     return rotacao_simples_esquerda(pivo);
// }

// arvore_avl rotacao(arvore_avl pivo) {
//     if (pivo->fb > 0) {
//         // Rotação esquerda
//         if (pivo->dir->fb >= 0) {
//             if (pivo->dir->fb == 0) {
//                 pivo->fb = 1;
//                 pivo->dir->fb = -1;
//             } else {
//                 pivo->fb = 0;
//                 pivo->dir->fb = 0;
//                 // rotação simples esquerda
//                 return rotacao_simples_esquerda(pivo);
//             }
//         } else {
//             pivo->fb = 0;
//             pivo->dir->fb = 0;
//             // rotação dupla esquerda
//             return rotacao_dupla_esquerda(pivo);
//         }
//     } else {
//         // Rotação direita
//         if (pivo->esq->fb <= 0) {
//             if (pivo->esq->fb == 0) {
//                 pivo->fb = 1;
//                 pivo->esq->fb = -1;
//             } else {
//                 pivo->fb = 0;
//                 pivo->esq->fb = 0;
//                 // rotação simples direita
//                 return rotacao_simples_direita(pivo);
//             }
//         } else {
//             pivo->fb = 0;
//             pivo->esq->fb = 0;
//             // rotação dupla direita
//             return rotacao_dupla_direita(pivo);
//         }
//     }

//     return pivo;  
// }


// arvore_avl inserir(arvore_avl raiz, int valor, int *cresceu){
//     //caso base
//     if(raiz == NULL) {
//         //1. Alocar espaço em memória
//         arvore_avl nova = (arvore_avl) malloc(sizeof(struct no));
//         //2. Inicializar o novo nó
//         nova->valor = valor;
//         nova->esq = NULL;
//         nova->dir = NULL;
//         nova->fb = 0;

//         //3. Retornar o ponteiro para a raiz (relativa) da nova árvore
//         *cresceu = 1;
//         return nova;
//     }
//     //caso indutivo
//     else {
//         if(valor > raiz->valor) {
//             raiz->dir = inserir(raiz->dir, valor, cresceu);
//             //após inserir, é preciso atualizar os fatores de balanço
//             //fator de balanço "atual" => raiz->fb
//             //sub-árvore cresceu ou não => *cresceu
//             if(*cresceu) {
//                 switch(raiz->fb) {
//                     case 0:
//                         raiz->fb = 1;
//                         *cresceu = 1;
//                         break;
//                     case 1:
//                         *cresceu = 0;
//                         return rotacao(raiz);
//                         break;
//                     case -1:
//                          raiz->fb = 0;
//                         *cresceu = 0;
//                         break;
//                 }
//             }
//         } else {
//             raiz->esq = inserir(raiz->esq, valor, cresceu);
//             if(*cresceu) {
//                 switch(raiz->fb) {
//                     case 0:
//                         raiz->fb = -1;
//                         *cresceu = 1;
//                         break;
//                     case 1:
//                         raiz->fb = 0;
//                         *cresceu = 0;
//                         break;
//                     case -1:
//                         *cresceu = 0;
//                         return rotacao(raiz);
//                         break;
//                 }
//         }
//     }
//     return raiz;
// }
// }

#ifndef TABELA_H
#define TABELA_H

#include "bst.h"
#include "avl.h"
#include "rb.h"



typedef struct tabela {
    FILE *arquivo_dados;
    arvore_bst indice_bst;
    // arvore_avl *indice_avl;
    // arvore_rb *indice_rb;
} tabela;

int inicializarTabela(tabela *tabela);
void finalizarTabela(tabela *tabela);
void adicionarRegistro(tabela *tabela, dado novoDado);


#endif
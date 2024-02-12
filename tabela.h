#ifndef TABELA_H
#define TABELA_H

#include "bst.h"
#include "avl.h"
#include "rb.h"


typedef struct tabela {
    FILE *arquivo_dados;
    arvore_bst indice_bst;
    arvoreAVL indice_avl;
    arvore_rb indice_rb;
} tabela;



#endif
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "tabela.h"
#include "aluno.h"
#include <string.h>


void inicializar(arvore_bst *raiz) {
	*raiz = NULL;
}

int inicializarTabela(tabela *tab) {
	inicializar(&tab->indice_bst);	
	tab->arquivo_dados = fopen("dados.dat", "a+b");
	tab->indice_bst = carregar_arquivo("indices.dat", tab->indice_bst);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar (tabela *tab) {
	salvar_arquivo("indice_bst.dat", tab->indice_bst);
	fclose(tab->arquivo_dados);
}


dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));
	//__fpurge(stdin);
	getchar();
	printf("nome: ");
	fgets(novo->nome, 80,  stdin);
	tirar_enter(novo->nome);
	printf("curso: ");
	fgets(novo->curso, 50,  stdin);
	tirar_enter(novo->curso);
	printf("matricula: ");
	scanf("%d", &novo->matricula);
	printf("idade: ");
	scanf("%d", &novo->idade);
	printf("media: ");
	scanf("%f", &novo->media);
	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore_bst a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore_bst raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_bst), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}

arvore_bst carregar_arquivo(char *nome, arvore_bst a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_bst * temp;
	if(arq != NULL) {
		temp = (tipo_bst *) malloc(sizeof(tipo_bst));
		while(fread(temp, sizeof(tipo_bst), 1, arq)) {
			
			a = adicionar(temp, a);			
			temp = (tipo_bst *) malloc(sizeof(tipo_bst));

		}
		fclose(arq);

	}
	return a;
}


void atualizar_indices_bst(arvore_bst raiz, int novo_indice) {
    if (raiz != NULL) {
        raiz->dado->indice = novo_indice;
        atualizar_indices_bst(raiz->esq, novo_indice);
        atualizar_indices_bst(raiz->dir, novo_indice);
    }
}


void adicionarAluno(tabela *tab, dado *aluno){
	if(tab->arquivo_dados != NULL) {
			tipo_bst * novo = (tipo_bst *) malloc(sizeof(tipo_bst));

			novo->matricula = aluno->matricula;

			fseek(tab->arquivo_dados, 0L, SEEK_END);
			novo->indice = ftell(tab->arquivo_dados);

			fwrite(aluno, sizeof(dado), 1, tab->arquivo_dados);
			tab->indice_bst = adicionar(novo, tab->indice_bst);
	}
}



arvore_bst adicionar (tipo_bst *valor, arvore_bst raiz) {
	if(raiz == NULL) {
		arvore_bst novo = (arvore_bst) malloc(sizeof(struct no_bst));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if(valor->matricula > raiz->dado->matricula) {
		raiz->dir = adicionar(valor, raiz->dir);
	} else {
		raiz->esq = adicionar(valor, raiz->esq);
	}
	return raiz;
}


// int maior(arvore_bst no) {
//     // Encontrar o elemento mais à direita da árvore
//     while (no->dir != NULL) {
//         no = no->dir;
//     }
//     return no->dado;
// }


// int altura(arvore_bst raiz) {
// 	if(raiz == NULL) {
// 		return 0;
// 	}
// 	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
// }



tipo_bst * maior_elemento(arvore_bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_bst * menor_elemento(arvore_bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore_bst raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void pos_order(arvore_bst raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}
}

void in_order(arvore_bst raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
}

void imprimir_elemento(arvore_bst raiz, tabela * tab) {
	dado * temp = (dado *) malloc (sizeof(dado));
    temp->matricula = 1000;
    printf("indice: %d\n", raiz->dado->indice);

   	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	//
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

	printf("\nMatricula: %d \nR:%d \nNome:%s \nCurso:%s \nIdade:%d \nMedia:%2.f \n", raiz->dado->matricula,r, temp->nome, temp->curso, temp->idade, temp->media);
	free(temp);
}


arvore_bst remover_bst(arvore_bst raiz, int matricula) {
    if (raiz == NULL) {
        printf("Arvore vazia");
        return NULL;
    }

    if (raiz->dado->matricula == matricula) {
        // caso 1: elemento não possui filhos
        if (raiz->dir == NULL && raiz->esq == NULL) {
            free(raiz);
            return NULL;
        }

        // caso 2a: elemento possui exatamente um filho(esq)
        if (raiz->dir == NULL && raiz->esq != NULL) {
            arvore_bst retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

        // caso 2b: elemento possui exatamente um filho(dir)
        if (raiz->esq == NULL && raiz->dir != NULL) {
            arvore_bst retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        // caso 3: dois filhos
        if (raiz->esq != NULL && raiz->dir != NULL) {
            arvore_bst temp = raiz->esq;
            arvore_bst maiorEsquerda = procuraMaiorEsquerda(temp);

            // copiar o valor desse elemento para a raiz relativa
            raiz->dado->matricula = maiorEsquerda->dado->matricula;

            // remover a duplicata NA SUB-ÁRVORE ESQ
            raiz->esq = remover_bst(raiz->esq, maiorEsquerda->dado->matricula);
        }
    } else {
		if(raiz->dado->matricula > matricula){
            raiz->esq = remover_bst(raiz->esq, matricula);
        } else {
            raiz->dir = remover_bst(raiz->dir, matricula);
        }
	}

    return raiz;
}


arvore_bst procuraMaiorEsquerda(arvore_bst raiz){
    arvore_bst no1 = raiz;
    arvore_bst no2 = raiz->dir;

    while(no2 != NULL){
        no1 = no2;
        no2 =no2->dir;
    }    
    return no1;
}


#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "tabela.h"
#include <string.h>


void inicializar(arvore_bst *raiz) {
	*raiz = NULL;
}

int inicializarTabela(tabela *tab) {
	tab->indice_bst = NULL;
	inicializar((no_bst **)&tab->indice_bst);	
	tab->arquivo_dados = fopen("dados.dat", "r+b");
    tab->indice_bst = carregar_arquivo("indice_bst.dat", &tab->indice_bst);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo("indice_bst.dat", tab->indice_bst);
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
	size_t length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';  // Substituir '\n' por '\0'
    }
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
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}

arvore_bst carregar_arquivo(char *nome, arvore_bst *a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
			
		    *a = adicionar(temp, *a);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return *a;
}

void atualizar_indices_bst(arvore_bst raiz, int novo_indice) {
    if (raiz != NULL) {
        raiz->dado->indice = novo_indice;
        atualizar_indices_bst(raiz->esq, novo_indice);
        atualizar_indices_bst(raiz->dir, novo_indice);
    }
}


void adicionarAluno(tabela *tab, dado *aluno) {
    if (tab->arquivo_dados != NULL) {
        tipo_dado *novo = (tipo_dado *)malloc(sizeof(tipo_dado));
        if (novo == NULL) {
            fprintf(stderr, "Erro: Falha na alocação de memória no adicionarAluno.\n");
            exit(EXIT_FAILURE);
        }

		novo->chave_nome = strdup(aluno->nome);
		tirar_enter(novo->chave_nome);

        fseek(tab->arquivo_dados, 0L, SEEK_END);
        novo->indice = ftell(tab->arquivo_dados);



        fwrite(aluno, sizeof(tipo_dado), 1, tab->arquivo_dados);
		fwrite(&aluno->matricula, sizeof(int), 1, tab->arquivo_dados);
		fwrite(&aluno->idade, sizeof(int), 1, tab->arquivo_dados);
		fwrite(&aluno->media, sizeof(float), 1, tab->arquivo_dados);

        tab->indice_bst = adicionar(novo, tab->indice_bst);
		// Atualizar os índices na árvore BST
        atualizar_indices_bst(tab->indice_bst, novo->indice);
    }
}

int comparar_nomes(const char *nome1, const char *nome2) {
    return strcmp(nome1, nome2);
}

arvore_bst adicionar(tipo_dado *valor, arvore_bst raiz) {
    if (raiz == NULL) {
        arvore_bst novo = (arvore_bst)malloc(sizeof(struct no_bst));
        if (novo == NULL) {
            fprintf(stderr, "Erro: Falha na alocação de memória no adicionar.\n");
            exit(EXIT_FAILURE);
        }
        novo->dado = (tipo_dado *)malloc(sizeof(tipo_dado));
        if (novo->dado == NULL) {
            free(novo);
            fprintf(stderr, "Erro: Falha na alocação de memória no adicionar.\n");
            exit(EXIT_FAILURE);
        }
        // Usar strncpy para copiar os dados da estrutura
        strncpy(novo->dado->chave_nome, valor->chave_nome, sizeof(novo->dado->chave_nome) - 1);
        novo->dado->chave_nome[sizeof(novo->dado->chave_nome) - 1] = '\0';  // Garantir que o campo termine com '\0'
        novo->dado->indice = valor->indice;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    int comparacao = comparar_nomes(valor->chave_nome, raiz->dado->chave_nome);

    if (comparacao > 0) {
        raiz->dir = adicionar(valor, raiz->dir);
    } else if (comparacao < 0) {
        raiz->esq = adicionar(valor, raiz->esq);
    }
    return raiz;
}



int altura(arvore_bst raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

tipo_dado * maior_elemento(arvore_bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_dado * menor_elemento(arvore_bst raiz) {
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
	if (temp == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória no imprimir_elemento\n");
        exit(EXIT_FAILURE);
    }
    
    printf("indice: %d\n", raiz->dado->indice);

   	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

	printf("[%s, %s, %d, %d, %.2f]\n", raiz->dado->chave_nome, temp->curso, temp->idade, temp->matricula, temp->media);
	free(temp);
}

//Função para remover um nó da árvore BST por nome
arvore_bst remover_bst(char *valor, arvore_bst raiz) {
    if (raiz == NULL)
        return NULL;

    if (strcmp(raiz->dado->chave_nome, valor) == 0) {
        if (raiz->esq == NULL) {
            return raiz->dir;
        }
        if (raiz->dir == NULL) {
            return raiz->esq;
        }

        // Substituir o nó a ser removido pelo maior elemento da subárvore esquerda
        tipo_dado *maior = maior_elemento(raiz->esq);
        
        // Fazer uma cópia dos dados
        tipo_dado *copiamaior = (tipo_dado *)malloc(sizeof(tipo_dado));
        if (copiamaior == NULL) {
            // Lidar com falha na alocação de memória
            exit(EXIT_FAILURE);
        }
        memcpy(copiamaior, maior, sizeof(tipo_dado));
        
        // Substituir o dado na raiz
        free(raiz->dado);  // Liberar a memória dos dados antigos
        raiz->dado = copiamaior;

        raiz->esq = remover_bst(maior->chave_nome, raiz->esq);  // Recursivamente remover o nó

        return raiz;
    }

    if (strcmp(valor, raiz->dado->chave_nome) > 0) {
        raiz->dir = remover_bst(valor, raiz->dir);
    } else {
        raiz->esq = remover_bst(valor, raiz->esq);
    }

    return raiz;
}

int buscar_indice_bst(char *chave_nome, arvore_bst raiz) {
    if (raiz == NULL) {
        return -1;  // Chave não encontrada na árvore
    }

    int comparacao = comparar_nomes(chave_nome, raiz->dado->chave_nome);

    if (comparacao == 0) {
        return raiz->dado->indice;  // Chave encontrada, retornar o índice
    } else if (comparacao < 0) {
        return buscar_indice_bst(chave_nome, raiz->esq);  // Buscar na subárvore esquerda
    } else {
        return buscar_indice_bst(chave_nome, raiz->dir);  // Buscar na subárvore direita
    }
}



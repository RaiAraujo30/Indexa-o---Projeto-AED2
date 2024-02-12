#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "tabela.h"
#include <string.h>

// Função para inicializar uma árvore AVL
void inicializar_avl(arvoreAVL *raiz) {
    *raiz = NULL;
}


// // Função para inicializar a tabela, incluindo_avl a leitura do arquivo de índice
// int inicializarTabelaAvl(tabela *tab) {
//     tab->indice_avl = NULL;
//     inicializar_avl((arvoreAVL *)&tab->indice_avl);
//     int cresceu = 0;

//     tab->arquivo_dados = fopen("dados.dat", "r+b");
//     tab->indice_avl = carregar_arquivoAvl("indice_avl.dat", tab->indice_avl);

//     if (tab->arquivo_dados != NULL)
//         return 1;
//     else
//         return 0;
// }

// Função para liberar a memória alocada pela árvore AVL e fechar o arquivo de dados
void finalizar_avl(tabela *tab) {
    salvar_arquivoAvl("indice_avl.dat", tab->indice_avl);
    fclose(tab->arquivo_dados);
}

// Função para remover o '\n' do final da string
void tirar_enter_avl(char *string) {
    size_t length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';  // Substituir '\n' por '\0'
    }
}

// Função para ler os dados de um aluno do usuário
dado * ler_dados_avl() {
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



// Função auxiliar para salvar a árvore AVL em um arquivo
void salvar_auxiliarAvl(arvoreAVL raiz, FILE *arq) {
    if (raiz != NULL) {
        fwrite(raiz->dado, sizeof(tipo_avl), 1, arq);
        salvar_auxiliarAvl(raiz->esq, arq);
        salvar_auxiliarAvl(raiz->dir, arq);
    }
}
// Função para salvar a árvore AVL em um arquivo
void salvar_arquivoAvl(char *nome, arvoreAVL a) {
    FILE *arq;
    arq = fopen(nome, "wb");
    if (arq != NULL) {
        salvar_auxiliarAvl(a, arq);
        fclose(arq);
    }
}


// Função para carregar a árvore AVL a partir de um arquivo
arvoreAVL carregar_arquivoAvl(char *nome, arvoreAVL a) {
    FILE *arq;
    arq = fopen(nome, "rb");
    tipo_avl *temp;

    if (arq != NULL) {
        temp = (tipo_avl *)malloc(sizeof(tipo_avl));
        while (fread(temp, sizeof(tipo_avl), 1, arq)) {

           
            a = inserir_avl(a, temp,NULL);

            
        }
        fclose(arq);
        free(temp);
    }

    return a;
}

void imprimir_elemento_avl(arvoreAVL raiz, tabela *tab) {
    dado *temp = (dado *)malloc(sizeof(dado));
    temp->idade = 1000;  // Consideração: Valor inicial arbitrário, ajuste conforme necessário
    printf("\nindice: %d\n", raiz->dado->indice);

    fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);

    // Atualização da posição do cursor no arquivo pode ser necessária aqui, dependendo das operações anteriores

    int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

    if (r != 1) {
        fprintf(stderr, "Erro ao ler dados do arquivo\n");
        free(temp);
        return;  // Tratamento de erro na leitura do arquivo
    }

    printf("Idade: %d\n r: %d \nNome: %s \nCurso: %s \nMatricula: %d \nMedia: %.2f\n", raiz->dado->idade, r, temp->nome, temp->curso,temp->matricula,  temp->media);

    free(temp);
}



// TA ERRADO
// Função para adicionar um aluno à tabela
void adicionarAlunoAvl(tabela *tab, dado *aluno){
    int cresceu = 0;
    if(tab->arquivo_dados != NULL) {
        tipo_avl * novo = (tipo_avl *) malloc(sizeof(tipo_avl));

        novo->idade = aluno->idade;

        fseek(tab->arquivo_dados, 0L, SEEK_END);
        novo->indice = ftell(tab->arquivo_dados);

        if (fwrite(aluno, sizeof(dado), 1, tab->arquivo_dados) != 1) {
            fprintf(stderr, "Erro ao escrever dados no arquivo.\n");
            free(novo);
            return;  // Tratamento de erro na escrita no arquivo
        }

        // Inserir na árvore AVL
        tab->indice_avl = inserir_avl(tab->indice_avl, novo, &cresceu);
    }
}




arvoreAVL rotacao_simples_esquerda(arvoreAVL pivo) {
    //inicialização
    arvoreAVL u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;


    //Atualização dos ponteiros
    u->esq = pivo;
    pivo->dir = t2;

    return u;

}

arvoreAVL rotacao_simples_direita(arvoreAVL pivo){
    arvoreAVL u, t1, t2, t3;
    u = pivo->esq;
    t3 = pivo->dir;
    t1 = u->esq;
    t2 = u->dir;

    //Atualizando os ponteiros
    u->dir = pivo;
    pivo->esq = t2;

    return u;
}

arvoreAVL rotacao_dupla_direita(arvoreAVL pivo) {
    pivo->esq = rotacao_simples_esquerda(pivo->esq);
    return rotacao_simples_direita(pivo);
}

arvoreAVL rotacao_dupla_esquerda(arvoreAVL pivo) {
    pivo->dir = rotacao_simples_direita(pivo->dir);
    return rotacao_simples_esquerda(pivo);
}

arvoreAVL rotacao_avl(arvoreAVL pivo) {

        if(pivo->fb > 0) {
            //Rotação esquerda
            if(pivo->dir->fb >= 0) {
                if(pivo->dir->fb == 0) {
                    pivo->fb = 1;
                    pivo->dir->fb = -1;
                } 
                else{
                    pivo->fb = 0;
                    pivo->dir->fb = 0;
                }
                //rotação simples esquerda
                pivo = rotacao_simples_esquerda(pivo);
            } 
            else {
                //rotação dupla esquerda

                if(pivo->dir->esq->fb == -1) {
                    pivo->fb = 0;
                    pivo->dir->fb = 1;
                    pivo->dir->esq->fb = 0;
                } 
                else if(pivo->dir->esq->fb == 0){
                    pivo->fb = 0;
                    pivo->dir->fb = 0;//mudança teste, 1 para 0
                    pivo->dir->esq->fb = 0;//mudança teste, 1 para 0
                }
                else{
                    pivo->fb = -1;//mudança teste, 1 para -1
                    pivo->dir->fb = 0;
                    pivo->dir->esq->fb = 0;//mudança teste, 1 para 0
                }
                pivo = rotacao_dupla_esquerda(pivo);
            }
        }
    else {

        //Rotação direita
        if(pivo->esq->fb <= 0) {
            if(pivo->esq->fb == 0) {
                pivo->fb = -1;
                pivo->esq->fb = 1;

                //rotação simples direita
                pivo = rotacao_simples_direita(pivo);
            } 
            else{
                pivo->fb = 0;
                pivo->esq->fb = 0;

                //rotação simples direita
                pivo = rotacao_simples_direita(pivo);
            }
        }
        
        else {
        //rotação dupla direita

            if(pivo->esq->dir->fb == -1) {
                pivo->fb = 1;
                pivo->esq->fb = 0;
                pivo->esq->dir = 0;
            } 
            else if(pivo->esq->dir->fb == 0){
                pivo->fb = 0;
                pivo->esq->fb = 0;
                pivo->esq->dir->fb = 0;
            }
            else{
                pivo->fb = 0;
                pivo->esq->fb = -1;
                pivo->esq->dir->fb = 0;
            }
            pivo = rotacao_dupla_direita(pivo); 
        }
    }
    return pivo;
}

arvoreAVL inserir_avl(arvoreAVL raiz, tipo_avl *valor, int *cresceu){
    if(raiz == NULL) {
        arvoreAVL nova = (arvoreAVL) malloc(sizeof(struct no));
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;
        nova->dado = valor;

        *cresceu = 1;
        return nova;
    } else {
        if (valor->idade > raiz->dado->idade) {
            raiz->dir = inserir_avl(raiz->dir, valor, cresceu);

            if (*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 0;
                        break;
                    case 1:
                        *cresceu = 1;
                        return rotacao_avl(raiz);
                        break;
                    case -1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserir_avl(raiz->esq, valor, cresceu);

            if (*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 0;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case -1:
                        *cresceu = 1;
                        return rotacao_avl(raiz);
                        break;
                }
            }
        }
        return raiz;
    }
}


void in_order_Avl(arvoreAVL raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order_Avl(raiz->esq, tab);
		imprimir_elemento_avl(raiz, tab);
		in_order_Avl(raiz->dir, tab);
	}
}

int pai_Avl(arvoreAVL raiz, int i){


   if (raiz->valor == i ){
            printf("-1");
        }
    if ((raiz->esq != NULL && raiz->esq->valor == i) || (raiz->dir != NULL && raiz->dir->valor == i)){
            printf("[%d]", raiz->valor);
            
        }else {
        
        if (i < raiz->valor) {
            pai_Avl(raiz->esq, i);
        } else if (i > raiz->valor) {
            pai_Avl(raiz->dir, i);
        } else {
            printf("-1\n");
        }
    }

}


arvoreAVL busca_Avl(int valor, arvoreAVL raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->valor == valor) {
        return raiz;
    } else {
        if (valor >= raiz->valor) {
            return busca_Avl(valor, raiz->dir);
        } else {
            return busca_Avl(valor, raiz->esq);
        }
    }
}
int altura_Avl(arvoreAVL raiz){
    if (raiz == NULL) {
        return 0; 
    }
    int contadoresq = 0;
    if(raiz->valor % 1 == 0){
        contadoresq++; 
        } 
    int contadordir = 0;
    if(raiz->valor % 1 == 0){
        contadordir++; 
        } 
    contadoresq += altura_Avl(raiz->esq);
    contadordir += altura_Avl(raiz->dir);

    if(contadordir > contadoresq){
        return contadordir;
    } else{
        return contadoresq;
    }
}

int maior(arvoreAVL no) {
    // Encontrar o elemento mais à direita da árvore
    while (no->dir != NULL) {
        no = no->dir;
    }
    return no->valor;
}

arvoreAVL remover_avl(arvoreAVL raiz, int indice, int *decresceu){

    //caso base
    if(raiz == NULL){
        *decresceu = 0; 
        return NULL;
    }
    //caso geral
    else{

        if(raiz->dado->indice == indice){
            //sem filhos
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                *decresceu = 1;
                return NULL;
            }
            else{
                //um filho
                if(raiz->esq == NULL || raiz->dir == NULL){
                    arvoreAVL nova;
                    if (raiz->esq == NULL){
                        nova = raiz->dir;
                    }
                    else{
                        nova = raiz->esq;
                    }
                    free(raiz);
                    *decresceu = 1;
                    return nova;
                }
                //dois filhos
                else if(raiz->esq != NULL && raiz->dir != NULL){
                    arvoreAVL nova = raiz->esq;

                    while(nova->dir != NULL){
                        nova = nova->dir;
                    }
                    raiz->dado->indice = nova->dado->indice;
                    //nova->dado->idade ou idade??
                    raiz->esq = remover_avl(raiz->esq, nova->dado->indice, decresceu);

                    switch (raiz->fb){
                        case 0:
                            if(!*decresceu){ 
                                raiz->fb = 0;
                                *decresceu = 0;
                            }
                            else{
                                raiz->fb = 1;
                                *decresceu = 0;
                            }
                            break;
                        case -1:
                            if(!*decresceu){ 
                                raiz->fb = -1;
                                *decresceu = 0;
                            }
                            else{
                                raiz->fb = 0;
                                *decresceu = 1;
                            }
                            break; 
                        case 1:
                            *decresceu = 1;
                            raiz = rotacao_avl(raiz);
                            break;
                    }
                    return raiz;
                }
            }
        }

        else{
            //chamadas recursivas
            if(raiz->dado->indice > indice){
                raiz->esq = remover_avl(raiz->esq, indice, decresceu);

                if(*decresceu) {
                    switch(raiz->fb){
                        case 0:
                            raiz->fb = 1;
                            *decresceu = 0;
                            break;
                        case 1:
                            if(raiz->dir->fb == 0){
                                *decresceu = 0;
                            }
                            else{
                                *decresceu = 1;
                            }
                            return rotacao_avl(raiz);
                            break;
                        case -1:
                            *decresceu = 1;
                            raiz->fb = 0;
                            break;
                    }
                }
            }
            else if(raiz->dado->indice < indice){
               raiz->dir = remover_avl(raiz->dir, indice, decresceu);

                if(*decresceu){
                    switch(raiz->fb){
                        case 0:
                            raiz->fb = -1;
                            *decresceu = 0;
                            break;
                        case 1:
                            *decresceu = 1;
                            raiz->fb = 0;
                            break;
                        case -1:
                            if(raiz->esq->fb == 0){
                                *decresceu = 0;
                            }
                            else{
                                *decresceu = 1;
                            }
                            return rotacao_avl(raiz);
                            break;
                    }
                }
            }
        }
        return raiz;
    }
}

// Função para buscar um aluno por idade na árvore AVL
arvoreAVL buscaPorIdade(arvoreAVL raiz, int idade) {
    if (raiz == NULL || raiz->dado->idade == idade) {
        return raiz;
    }

    if (idade < raiz->dado->idade) {
        return buscaPorIdade(raiz->esq, idade);
    } else {
        return buscaPorIdade(raiz->dir, idade);
    }
}
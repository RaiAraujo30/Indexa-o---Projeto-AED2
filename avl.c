#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "tabela.h"
#include <string.h>

// Função para inicializar uma árvore AVL
void inicializar(arvoreAVL *raiz) {
    *raiz = NULL;
}


// Função para inicializar a tabela, incluindo a leitura do arquivo de índice
int inicializarTabela(tabela *tab) {
    tab->indice_avl = NULL;
    inicializar((arvoreAVL *)&tab->indice_avl);

    tab->arquivo_dados = fopen("dados.dat", "r+b");
    tab->indice_avl = carregar_arquivo("indice_avl.dat", &tab->indice_avl);

    if (tab->arquivo_dados != NULL)
        return 1;
    else
        return 0;
}

// Função para liberar a memória alocada pela árvore AVL e fechar o arquivo de dados
void finalizar(tabela *tab) {
    fclose(tab->arquivo_dados);
    salvar_arquivo("indice_avl.dat", tab->indice_avl);
}

// Função para ler os dados de um aluno do usuário
dado *ler_dados() {
    dado *novo = (dado *)malloc(sizeof(dado));
    getchar();
    printf("Nome: ");
    fgets(novo->nome, 3, stdin);
    printf("Curso: ");
    fgets(novo->curso, 3, stdin);
    printf("Matrícula: ");
    scanf("%d", &novo->matricula);
    printf("Idade: ");
    scanf("%d", &novo->idade);
    printf("Média: ");
    scanf("%f", &novo->media);

    return novo;
}

// Função para remover o '\n' do final da string
void tirar_enter(char *string) {
    size_t length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';  // Substituir '\n' por '\0'
    }
}

// Função para salvar a árvore AVL em um arquivo
void salvar_arquivo(char *nome, arvoreAVL a) {
    FILE *arq;
    arq = fopen(nome, "wb");
    if (arq != NULL) {
        salvar_auxiliar(a, arq);
        fclose(arq);
    }
}

// Função auxiliar para salvar a árvore AVL em um arquivo
void salvar_auxiliar(arvoreAVL raiz, FILE *arq) {
    if (raiz != NULL) {
        fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
        salvar_auxiliar(raiz->esq, arq);
        salvar_auxiliar(raiz->dir, arq);
    }
}

// Função para carregar a árvore AVL a partir de um arquivo
arvoreAVL carregar_arquivo(char *nome, arvoreAVL *a) {
    FILE *arq;
    arq = fopen(nome, "rb");
    tipo_dado *temp;

    if (arq != NULL) {
        temp = (tipo_dado *)malloc(sizeof(tipo_dado));
        while (fread(temp, sizeof(tipo_dado), 1, arq)) {
            *a = inserir(*a, temp->chave, 0, temp->indice);
            temp = (tipo_dado *)malloc(sizeof(tipo_dado));
        }
        fclose(arq);
    }

    return *a;
}

// Função para adicionar um aluno à tabela
void adicionarAluno(tabela *tab, dado *aluno) {
    if (tab->arquivo_dados != NULL) {
        tipo_dado *novo = (tipo_dado *)malloc(sizeof(tipo_dado));
        if (novo == NULL) {
            fprintf(stderr, "Erro: Falha na alocação de memória no adicionarAluno.\n");
            exit(EXIT_FAILURE);
        }

        novo->chave = aluno->matricula;
        novo->indice = ftell(tab->arquivo_dados);

        fwrite(aluno, sizeof(tipo_dado), 1, tab->arquivo_dados);
        fwrite(&aluno->matricula, sizeof(int), 1, tab->arquivo_dados);
        fwrite(&aluno->idade, sizeof(int), 1, tab->arquivo_dados);
        fwrite(&aluno->media, sizeof(float), 1, tab->arquivo_dados);

        tab->indice_bst = inserir(tab->indice_bst, novo->chave, 0, novo->indice);
    }
}

void liberar_arvore(no *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz->dado);
        free(raiz);
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

arvoreAVL rotacao(arvoreAVL pivo) {
    if (pivo->fb > 0) {
        // Rotação esquerda
        if (pivo->dir->fb >= 0) {
            if (pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
                // rotação simples esquerda
                return rotacao_simples_esquerda(pivo);
            }
        } else {
            // rotação dupla esquerda
            pivo->fb = 0;
            pivo->dir->fb = 0;
            return rotacao_dupla_esquerda(pivo);
        }
    } else {
        // Rotação direita
        if (pivo->esq->fb <= 0) {
            if (pivo->esq->fb == 0) {
                pivo->fb = 1;
                pivo->esq->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
                // rotação simples direita
                return rotacao_simples_direita(pivo);
            }
        } else {
            pivo->fb = 0;
            pivo->esq->fb = 0;
            // rotação dupla direita
            return rotacao_dupla_direita(pivo);
        }
    }

    return pivo;  
}


arvoreAVL inserir(arvoreAVL raiz, int valor, int *cresceu, int indice){
    //caso base
    if(raiz == NULL) {
        //1. Alocar espaço em memória
        arvoreAVL nova = (arvoreAVL) malloc(sizeof(struct no));
        //2. Inicializar o novo nó
        nova->valor = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;
        nova->dado = (tipo_dado *)malloc(sizeof(tipo_dado));
            if (nova->dado == NULL) {
                free(nova);
                fprintf(stderr, "Erro: Falha na alocação de memória.\n");
                exit(EXIT_FAILURE);
            }
            nova->dado->indice = indice;

        //3. Retornar o ponteiro para a raiz (relativa) da nova árvore
        *cresceu = 1;
        return nova;
    }
    //caso indutivo
    else {
        if(indice > raiz->dado->indice) {
            raiz->dir = inserir(raiz->dir, valor, cresceu, indice);
            //após inserir, é preciso atualizar os fatores de balanço
            //fator de balanço "atual" => raiz->fb
            //sub-árvore cresceu ou não => *cresceu
            if(*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacao(raiz);
                        break;
                    case -1:
                         raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserir(raiz->esq, valor, cresceu, indice);
            if(*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case -1:
                        *cresceu = 0;
                        return rotacao(raiz);
                        break;
                }
        }
    }
    return raiz;
}
}




void pre_order(arvoreAVL raiz){
    if(raiz != NULL){
        printf("[%d]", raiz->valor);

        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

void in_order(arvoreAVL raiz){
    if(raiz != NULL){
        

        in_order(raiz->esq);
        printf("[%d]", raiz->valor);
        in_order(raiz->dir);
    }
}


void pos_order(arvoreAVL raiz){
    if(raiz != NULL){
        pre_order(raiz->esq);
        pre_order(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}

void exibir_reverso(arvoreAVL raiz){
    if(raiz != NULL) {
      
    exibir_reverso(raiz->dir);
    printf("[%d]", raiz->valor);
    exibir_reverso(raiz->esq);
    
    
}
}
int qtd_par(arvoreAVL raiz){
    if (raiz == NULL) {
        return 0; 
    }
    int contador = 0;

    if(raiz->valor % 2 == 0){
       contador++; 
    }  
    contador += qtd_par(raiz->esq);
    contador += qtd_par(raiz->dir);

    return contador;
}

int pai(arvoreAVL raiz, int i){


   if (raiz->valor == i ){
            printf("-1");
        }
    if ((raiz->esq != NULL && raiz->esq->valor == i) || (raiz->dir != NULL && raiz->dir->valor == i)){
            printf("[%d]", raiz->valor);
            
        }else {
        
        if (i < raiz->valor) {
            pai(raiz->esq, i);
        } else if (i > raiz->valor) {
            pai(raiz->dir, i);
        } else {
            printf("-1\n");
        }
    }

}

int somatorio(arvoreAVL raiz) {
    if (raiz == NULL) {
        return 0; 
    }

    int soma = raiz->valor; 
    soma += somatorio(raiz->esq);
    soma += somatorio(raiz->dir); 

    return soma;
}

int somatorio_par(arvoreAVL raiz){
     if (raiz == NULL) {
        return 0; 
    }

    int soma = 0;

    if (raiz->valor % 2 == 0){
        soma += raiz->valor;
    }
    soma += somatorio_par(raiz->esq);
    soma += somatorio_par(raiz->dir);

    return soma;

    }

arvoreAVL podar(arvoreAVL raiz, int i){
    if (raiz == NULL) {
        return 0; 
    }
    if (raiz->valor == i){
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    podar(raiz->esq, i);
    podar(raiz->dir, i);

    return raiz;
}

arvoreAVL busca(int valor, arvoreAVL raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->valor == valor) {
        return raiz;
    } else {
        if (valor >= raiz->valor) {
            return busca(valor, raiz->dir);
        } else {
            return busca(valor, raiz->esq);
        }
    }
}

void dobrar(arvoreAVL raiz){
    int dobro;
    if(raiz != NULL){
        dobro = (raiz->valor) * (raiz->valor);
        printf("[%d]", dobro);
        dobrar(raiz->esq);
        dobro = (raiz->valor) * (raiz->valor);  
        dobrar(raiz->dir);
    }

}


void filhos(arvoreAVL filha) {
    if (filha != NULL) {
        filhos(filha->esq);
        printf("[%d]", filha->valor);
        filhos(filha->dir);
    }
}
arvoreAVL descendentes(int valor,arvoreAVL raiz){
    
    if (raiz->valor == valor ){
        printf("Descendentes de [%d]: ", raiz->valor);
        filhos(raiz);
        printf("\n");
    } else{
        if(valor >= raiz->valor){
            return  descendentes(valor, raiz->dir);
        } else{
            return  descendentes(valor, raiz->esq);
        }
    }
}


int altura(arvoreAVL raiz){
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
    contadoresq += altura(raiz->esq);
    contadordir += altura(raiz->dir);

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

int fator_balanceamento(arvoreAVL N) {
    if (N == NULL)
        return 0;

    // Calcular a altura da subárvore esquerda e direita
    int altura_esq = altura(N->esq);
    int altura_dir = altura(N->dir);

    // Calcular e retornar o fator de balanceamento
    return altura_esq - altura_dir;
}

arvoreAVL remover(arvoreAVL raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Element to be deleted found

        // caso 1: elemento não possui filhos (folha)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // caso 2a: elemento possui exatamente um filho(esq)
        if (raiz->esq != NULL && raiz->dir == NULL) {
            arvoreAVL retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

        // caso 2b: elemento possui exatamente um filho(dir)
        if (raiz->esq == NULL && raiz->dir != NULL) {
            arvoreAVL retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        // caso 3: dois filhos
        if (raiz->esq != NULL && raiz->dir != NULL) {
            // localizar o maior elemento da subárvore esquerda
            raiz->valor = maior(raiz->esq);

            // remover a duplicata na subárvore esq
            raiz->esq = remover(raiz->esq, raiz->valor);
        }
    }

    // Realizar rotações, se necessário
    // Rotação à direita
    if (raiz->fb > 1 && valor < raiz->esq->valor) {
        return rotacao_simples_direita(raiz);
    }

    // Rotação à esquerda
    if (raiz->fb < -1 && valor > raiz->dir->valor) {
        return rotacao_simples_esquerda(raiz);
    }

    // Rotação dupla à esquerda e depois à direita
    if (raiz->fb > 1 && valor > raiz->esq->valor) {
        raiz->esq = rotacao_simples_esquerda(raiz->esq);
        return rotacao_simples_direita(raiz);
    }

    // Rotação dupla à direita e depois à esquerda
    if (raiz->fb < -1 && valor < raiz->dir->valor) {
        raiz->dir = rotacao_simples_direita(raiz->dir);
        return rotacao_simples_esquerda(raiz);
    }

    // Atualizar a altura do nó atual
    raiz->fb = fator_balanceamento(raiz);

    return raiz;
}


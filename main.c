#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "avl.h"
#include "rb.h"
#include "tabela.h"

int main(int argc, char *argv[]) {
    tabela tab;
    int opcao;
    inicializarTabela(&tab);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Altura da arvore\n");
        printf("2. Adicionar Aluno\n");
        printf("3. Maior elemento\n");
        printf("4. Menor elemento\n");
        printf("5. Percurso em Pre-Ordem\n");
        printf("6. Percurso em Ordem\n");
        printf("7. Percurso em Pos-Ordem\n");
        printf("10. Salvar arquivo\n");
        printf("11. Carregar arquivo\n");
        printf("12. Buscar indice pelo nome do aluno\n");
        printf("12. Buscar aluno pelo indice\n");
        printf("99. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Altura da arvore: %d\n", altura(tab.indice_bst));
                break;
            case 2:
                adicionarAluno(&tab, ler_dados());
                break;
            case 3:
                printf("Maior elemento: %s\n", maior_elemento(tab.indice_bst)->chave_nome);
                break;
            case 4:
                printf("Menor elemento: %s\n", menor_elemento(tab.indice_bst)->chave_nome);
                break;
            case 5:
                pre_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            case 6:
                in_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            case 7:
                pos_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            case 10:
                salvar_arquivo("dados.dat", tab.indice_bst);
                break;
            case 11:
                tab.indice_bst = carregar_arquivo("dados.dat", &tab.indice_bst);
                break;
            case 12:
            {
                char chave_procurada[3];
                printf("Digite o nome do aluno para buscar o índice: ");
                scanf("%s", chave_procurada);

                int indice_encontrado = buscar_indice_bst(chave_procurada, tab.indice_bst);

                if (indice_encontrado != -1) {
                    printf("Índice encontrado para a chave %s: %d\n", chave_procurada, indice_encontrado);
                } else {
                    printf("Aluno com o nome %s não encontrado.\n", chave_procurada);
                }
            }
            break;

            case 99:
                finalizar(&tab);
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

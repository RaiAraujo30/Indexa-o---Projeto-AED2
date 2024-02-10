
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "avl.h"
#include "rb.h"
#include "tabela.h"
#include "aluno.h"

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
        printf("12. remover um aluno\n");
        printf("99. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // printf("Altura da arvore: %d\n", altura(tab.indice_bst));
                // break;
            case 2:
            {

                dado *dados = ler_dados();
                adicionarAluno(&tab, dados);
                //adicionarAlunoAvl(&tab,ler_dados_avl());
                break;
            }
            case 3:
                printf("Maior elemento: %s\n", maior_elemento(tab.indice_bst)->matricula);
                break;
            case 4:
                printf("Menor elemento: %s\n", menor_elemento(tab.indice_bst)->matricula);
                break;
            case 5:
                pre_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            case 6:
                in_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            // case 7:
            //     pos_order(tab.indice_bst, &tab);
            //     printf("\n");
            //     break;
            case 10:
                salvar_arquivo("dados.dat", tab.indice_bst);
                break;
            case 11:
            {
                int cresceu;
				tab.indice_bst = carregar_arquivo("dados.dat", tab.indice_bst);
            	break;
            }
            case 12:
            {
                    int matricula;
                    printf("Digite a matrícula do aluno a ser removido: ");
                    scanf("%d", &matricula);

                    tab.indice_bst = remover_bst(tab.indice_bst, matricula);
                    break;
                }
			case 99:
				finalizar(&tab);
				exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

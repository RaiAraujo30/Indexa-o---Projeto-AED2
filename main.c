
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
        inicializarTabelaAvl(&tab);


    while (1) {
        printf("\nMenu:\n");
        printf("1. Altura da arvore\n");
        printf("2. Adicionar Aluno\n");
        printf("3. remover um aluno\n");
        printf("4. Percurso em Ordem\n");
        printf("5. Salvar arquivo\n");
        printf("6. Carregar arquivo\n");
       
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
                adicionarAlunoAvl(&tab,dados);
                break;
            }
            case 3:
               {
                    int matricula;
                    printf("Digite a matrícula do aluno a ser removido: ");
                    scanf("%d", &matricula);

                    tab.indice_bst = remover_bst(tab.indice_bst, matricula);
                    break;
                }
            case 4:
                 in_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            case 5:
               salvar_arquivo("dados.dat", tab.indice_bst);
               salvar_arquivoAvl("dados.dat", tab.indice_avl);
                break;
            case 6:
               {
                int cresceu;
				tab.indice_bst = carregar_arquivo("dados.dat", tab.indice_bst);
				tab.indice_avl = carregar_arquivoAvl("dados.dat", tab.indice_avl, &cresceu);
            	break;
            }
			case 99:
				finalizar(&tab);
				finalizar_avl(&tab);
				exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}


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
        printf("3. remover um aluno\n");
        printf("4. Percurso em Ordem (bst)\n");
        printf("5. Percurso em Ordem (avl)\n");
        printf("6. Salvar arquivo\n");
        printf("7. Carregar arquivo\n");
        printf("8. Buscar aluno pela matricula (indice bst)\n");
        printf("9. Buscar aluno pela idade (indice avl)\n");
       
        printf("99. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Altura da arvore: %d\n", altura_bst(tab.indice_bst));
                break;
            case 2:
            {

                dado *dados = ler_dados();
                adicionarAluno(&tab, dados);
               // adicionarAlunoAvl(&tab,dados);
                break;
            }
            case 3:
               {
                    int matricula;
                    printf("Digite o indice do aluno a ser removido: ");
                    scanf("%d", &matricula);
                    int decresceu =0;
                    tab.indice_bst = remover_bst(tab.indice_bst, matricula);
                    tab.indice_avl = remover_avl(tab.indice_avl, matricula, &decresceu);
                    
                    break;
                }
            case 4:
                 in_order(tab.indice_bst, &tab);
                printf("\n");
                break;
            case 5:
                 in_order_Avl(tab.indice_avl, &tab);
                printf("\n");
                break;  
            case 6:
               salvar_arquivo("dados.dat", tab.indice_bst);
               salvar_arquivoAvl("dados.dat", tab.indice_avl);
                break;
            case 7:
               {
                int cresceu;
				tab.indice_bst = carregar_arquivo("dados.dat", tab.indice_bst);
				tab.indice_avl = carregar_arquivoAvl("indice_avl.dat", tab.indice_avl);
            	break;
            }
            case 8:
            {
                int matriculaProcurada;
                printf("Digite a matricula do aluno: \n");
                scanf("%d", &matriculaProcurada);
                arvore_bst resultado = buscar_bst(tab.indice_bst, matriculaProcurada);

                if (resultado != NULL) {
                    printf("Aluno encontrado:\n");
                    imprimir_elemento(resultado, &tab);
                } else {
                    printf("Aluno nao encontrado.\n");
                }

                break;
            }
            case 9:
            {
                int matriculaProcurada;
                printf("Digite a idae do aluno: \n");
                scanf("%d", &matriculaProcurada);
                arvoreAVL resultado = buscaPorIdade(tab.indice_avl, matriculaProcurada);

                if (resultado != NULL) {
                    printf("Aluno encontrado:\n");
                    imprimir_elemento_avl(resultado, &tab);
                } else {
                    printf("Aluno nao encontrado.\n");
                }

                break;
            }
			case 99:
				finalizar(&tab);
				//finalizar_avl(&tab);
				exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

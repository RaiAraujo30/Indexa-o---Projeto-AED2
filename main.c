#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "tabela.h"


int main() {
    tabela minha_tabela;
    minha_tabela.arquivo_dados = fopen("dados.dat", "ab");
    minha_tabela.indice_bst = NULL;

    if (minha_tabela.arquivo_dados == NULL) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo de dados.\n");
        return EXIT_FAILURE;
    }

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar aluno\n");
        printf("2. Remover aluno\n");
        printf("3. Listar alunos\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Adicionar aluno
                {
                    dado *novo_aluno = ler_dados();
                    adicionarAluno(&minha_tabela, novo_aluno);
                    free(novo_aluno);
                    break;
                }
            case 2:
                // Remover aluno (implemente a lógica para remover)
                {
                    char nome[81];
                    printf("Digite o nome do aluno a ser removido: ");
                    scanf("%s", nome);
                    minha_tabela.indice_bst = remover_bst(nome, minha_tabela.indice_bst);
                    break;
                }
            case 3:
                // Listar alunos
                {
                    printf("\nLista de Alunos:\n");
                    // Utilize a função de impressão da árvore para listar os alunos
                    in_order(minha_tabela.indice_bst, &minha_tabela);
                    break;
                }
            case 0:
                // Sair
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Limpeza de memória e fechamento dos arquivos
    fclose(minha_tabela.arquivo_dados);
    // Liberar memória da árvore (implementação dependente da sua lógica de remoção)

    return 0;
}
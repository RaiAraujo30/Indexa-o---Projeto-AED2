// #include <stdio.h>
// #include <stdlib.h>
// #include "rb.h"
// #include "tabela.h"
// #include "string.h"

// arvore_rb no_null;

// /*
// Inicializa a árvore vazia com a raiz = null e inicializa o nó nulo duplo preto que será utilizado no método remover.
// */
// void inicializar_rb(arvore_rb *raiz) {
// 	*raiz = NULL;
// 	no_null = (arvore_rb) malloc(sizeof(struct no_rb));
// 	no_null->cor = DUPLO_PRETO;
// 	no_null->dado = 0;
//     no_null->esq = NULL;
//     no_null->dir = NULL;
//     no_null->pai = NULL;
// }

// void salvar_arquivo_rb(char *nome, arvore_rb a) {
// 	FILE *arq;
// 	arq = fopen(nome, "wb");
// 	if(arq != NULL) {
// 		salvar_auxiliar_rb(a, arq);
// 		fclose(arq);
// 	}
// }

// void salvar_auxiliar_rb(arvore_rb raiz, FILE *arq){
// 	if(raiz != NULL) {
// 		fwrite(raiz->dado, sizeof(tipo_rb), 1, arq);
// 		salvar_auxiliar_rb(raiz->esq, arq);
// 		salvar_auxiliar_rb(raiz->dir, arq);
// 	}

// }

// arvore_rb carregar_arquivo_rb(char *nome, arvore_rb a) {
// 	FILE *arq;
// 	arq = fopen(nome, "rb");
// 	tipo_rb * temp;
// 	if(arq != NULL) {
// 		temp = (tipo_rb *) malloc(sizeof(tipo_rb));
// 		while(fread(temp, sizeof(tipo_rb), 1, arq)) {
			
// 			adicionar_rb(temp, &a);			
			

// 		}
// 		fclose(arq);
// 		free(temp);

// 	}
// 	return a;
// }





// /* Adiciona um novo elemento na árvore.
// Parâmetros:
//     valor   - elemento a ser adicionado
//     raiz    - árvore onde o elemento será adicionado. 
//               Observe que este parâmetro é um ponteiro de ponteiro
// */
// void adicionar_rb (tipo_rb *valor, arvore_rb *raiz) {
// 	arvore_rb posicao, pai, novo;
//     //utiliza-se *raiz, por ser um ponteiro de ponteiro
// 	posicao = *raiz;
// 	pai = NULL;

// 	/*navega na árvore até encontrar a posição vaga apropriada para o elemento,
// 		nesta "descida" é necessário manter o ponteiro para o pai, pois após encontrar 
// 		a posição vaga (NULL) não seria possível navegar para o pai com o ponteiro posicao->pai */
// 	 while(posicao != NULL) {
// 			pai = posicao;
// 			if(valor->media > posicao->dado->media) 
// 					posicao = posicao->dir;
// 			else 
// 					posicao = posicao->esq;
// 	}


//     //Após achar a posição, inicializa o novo elemento
// 	novo = (arvore_rb) malloc(sizeof(struct no_rb));
// 	novo->dado->media = valor->media;
// 	novo->esq = NULL;
// 	novo->dir = NULL;
// 	novo->pai = pai;
// 	novo->cor = VERMELHO;

//     //Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
//     //Observe novamente o uso do ponteiro de ponteiro
// 	if(eh_raiz(novo))	
// 			*raiz = novo;
// 	else {
//         //Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento
// 		if(valor->media > pai->dado->media)
// 			pai->dir = novo;
// 		else
// 			pai->esq = novo;
// 	}

//     //Após inserir, verifica e ajusta a árvore resultante
// 	ajustar_rb(raiz, novo);
// }


// /* Verifica se a árvore está obedecendo todas as regras da RB e aplica as correções necessárias após a inserção.
// Parâmetros:
//     raiz - raiz (absoluta) da árvore
//     elemento - nó recentemente inserido que pode ter causado o desajuste da árvore
// */
// void ajustar_rb(arvore_rb *raiz, arvore_rb elemento){
//     //A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
//     //Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário
// 	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
// 			//caso 1: Cor do tio é vermelha, desce o preto do avô
// 			if(cor(tio(elemento)) == VERMELHO) {
// 				recolorir(avo(elemento));
// 				//tio(elemento)->cor = PRETO;
// 				//elemento->pai->cor = PRETO;
// 				//elemento->pai->pai->cor = VERMELHO;

// 				//Continua a verificação a partir do avô, que mudou para vermelho e pode ter 
// 				//gerado uma sequência vermelho-vermelho				
// 				elemento = elemento->pai->pai;
// 				continue;
// 			} 
// 			//caso 2a: rotação simples direita
// 			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
// 					rotacao_simples_direita_rb(raiz, elemento->pai->pai);
// 					recolorir(elemento->pai);
// 					//elemento->pai->cor = PRETO;
// 					//elemento->pai->dir->cor = VERMELHO;

// 					elemento = elemento->pai;
// 					continue;
// 			}
// 			//caso 2b: rotação simples esquerda
// 			if(!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
// 					rotacao_simples_esquerda_rb(raiz, elemento->pai->pai);
// 					recolorir(elemento->pai);
// 					//elemento->pai->cor = PRETO;
// 					//elemento->pai->esq->cor = VERMELHO;

// 					elemento = elemento->pai;
// 					continue;
// 			}
// 			//caso 3a: rotação dupla direita
// 			if(!eh_filho_esquerdo(elemento)&&
// 			    eh_filho_esquerdo(elemento->pai)&&
// 			   (tio(elemento) == NULL ||
// 				tio(elemento)->cor == PRETO)) {

// 					rotacao_dupla_direita_rb(raiz, elemento->pai->pai);
// 					recolorir(elemento);
// 					//rotacao_simples_esquerda(raiz, elemento->pai);
// 					//rotacao_simples_direita(raiz, elemento->pai);
// 					//elemento->cor = PRETO;
// 					//elemento->esq->cor = VERMELHO;
// 					//elemento->dir->cor = VERMELHO;
// 					continue;
// 			}
// 			//caso 3b: rotação dupla esquerda
// 			if(eh_filho_esquerdo(elemento)&&
// 			  !eh_filho_esquerdo(elemento->pai)&&
// 			  (tio(elemento) == NULL ||
// 			   tio(elemento)->cor == PRETO)) {

// 					rotacao_dupla_esquerda_rb(raiz, elemento->pai->pai);
// 					recolorir(elemento);
// 					//rotacao_simples_direita(raiz, elemento->pai);
// 					//rotacao_simples_esquerda(raiz, elemento->pai);
// 					//elemento->cor = PRETO;
// 					//elemento->dir->cor = VERMELHO;
// 					//elemento->esq->cor = VERMELHO;
// 					continue;
// 			}

// 	}
//     //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
// 	(*raiz)->cor = PRETO;
// }

// /* Realiza a rotação simples direita
// Antes da rotação: 
// cor(p) = Preto
// cor(u) = cor(v) = Vermelho

//        p             u
//       / \           / \
//      u  t2   =>    v   p
//     / \               / \
//    v  t1             t1 t2

// Após a rotação: 
// cor(u) = Preto
// cor(v) = cor(p) = Vermelho
// */
// void rotacao_simples_direita_rb(arvore_rb *raiz, arvore_rb pivo){
// 			arvore_rb u, t1;
// 			u = pivo->esq;
//             t1 = u->dir;

//             /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito*/
// 			int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
// 			//Atualização dos ponteiros
// 			pivo->esq = t1;
//             if(t1 != NULL)
// 				t1->pai = pivo;

// 			u->dir = pivo;

// 			u->pai = pivo->pai;
// 			pivo->pai = u;

//             //Se não existir árvore acima de u, u passa a ser a raiz da árvore
// 			if(eh_raiz(u))
// 				*raiz = u;
// 			else {
//               //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
// 					if(posicao_pivo_esq)
// 							u->pai->esq = u;
// 					else
// 							u->pai->dir = u;
// 			}
// }

// void rotacao_simples_esquerda_rb(arvore_rb *raiz, arvore_rb pivo) {
// 	arvore_rb u, t1;
// 	u = pivo->dir;
// 	t1= u->esq;
// 	/*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber 
// 	se o pivo p era um filho esquerdo ou direito*/
// 	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	
// 	//Atualização dos ponteiros
// 	pivo->dir = t1;
// 	if(t1 != NULL)
// 		t1->pai = pivo;

// 	u->esq = pivo;
// 	u->pai = pivo->pai;
// 	pivo->pai = u;

// 	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
// 	if(eh_raiz(u))
// 		*raiz = u;
// 	else {
//         /*Caso contrário (se existir) é preciso ligar o restante da árvore
// 		a esta sub-árvore, resultante da rotação*/
// 		if(posicao_pivo_esq)
// 			u->pai->esq = u;
// 		else
// 			u->pai->dir = u;
// 	}
// }

// void rotacao_dupla_direita_rb(arvore_rb *raiz, arvore_rb pivo) {
//     rotacao_simples_esquerda_rb(raiz, pivo->esq);
//     rotacao_simples_direita_rb(raiz, pivo);
// }
// void rotacao_dupla_esquerda_rb(arvore_rb *raiz, arvore_rb pivo){
//     rotacao_simples_direita_rb(raiz, pivo->dir);
//     rotacao_simples_esquerda_rb(raiz, pivo);
// }
// void recolorir(arvore_rb pivo){
	
// 	if(pivo->esq != NULL)
// 		pivo->esq->cor = pivo->cor;
// 	if(pivo->dir != NULL)
// 		pivo->dir->cor = pivo->cor;
// 	//se o pivô for preto, vai receber a cor vermelha e vice-versa
// 	pivo->cor = (pivo->cor == PRETO)? VERMELHO : PRETO;
// }

// /*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
// enum cor cor(arvore_rb elemento) {
// 	enum cor c;
// 	if(elemento==NULL)
// 		return PRETO;
// 	else
// 		return elemento->cor;
// 	return c;
// }
// /*Verifica se um nó é a raiz da árvore*/
// int eh_raiz(arvore_rb elemento) {
// 	return (elemento->pai == NULL);
// }
// /*Verifica se um nó é filho esquerdo*/
// int eh_filho_esquerdo(arvore_rb elemento) {
// 	return (elemento->pai != NULL && elemento == elemento->pai->esq);
// }

// arvore_rb tio(arvore_rb elemento) {
// 	return irmao(elemento->pai);
// }

// arvore_rb avo(arvore_rb elemento){
// 	return elemento->pai->pai;
// }

// arvore_rb irmao(arvore_rb elemento) {
// 	if(eh_filho_esquerdo(elemento))
// 		return elemento->pai->dir;
// 	else
// 		return elemento->pai->esq;
// }



// int altura_rb(arvore_rb raiz) {
// 	if(raiz == NULL) {
// 		return 0;
// 	}
// 	return 1 + maior_rb(altura_rb(raiz->dir), altura_rb(raiz->esq));
// }

// int maior_rb(int a, int b) {
// 	if(a > b)
// 		return a;
// 	else
// 		return b;
// }

// int maior_elemento_rb(arvore_rb raiz) {
// 	if(raiz == NULL)
// 			return -1;
// 	if(raiz->dir == NULL)
// 			return raiz->dado->media;
// 	else
// 			return maior_elemento_rb(raiz->dir);
// }

// int menor_elemento_rb(arvore_rb raiz) {
// 	if(raiz == NULL)
// 			return -1;
// 	if(raiz->esq == NULL)
// 			return raiz->dado->media;
// 	else
// 			return maior_elemento_rb(raiz->esq);
// }


// void in_order_rb(arvore_rb raiz, tabela *tab) {
// 	if(raiz != NULL) {
// 		in_order_rb(raiz->esq, tab);
// 		imprimir_elemento_rb(raiz,tab);
// 		in_order_rb(raiz->dir, tab);
// 	}
// }

// void imprimir_elemento_rb(arvore_rb raiz, tabela * tab) {
// 	dado * temp = (dado *) malloc (sizeof(dado));
//     temp->media = 1000;
//     printf("\nindice: %d\n", raiz->dado->indice);

//    	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
// 	//
// 	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

// 	printf("Matricula: %d \nR:%d \nNome:%s \nCurso:%s \nIdade:%d \nMedia:%2.f \n", temp->matricula,r, temp->nome, temp->curso,
//      temp->idade, raiz->dado->media);
// 	free(temp);
// }

// // void remover_rb (int valor, arvore_rb *raiz) {
// // 	arvore_rb posicao;
// // 	posicao = *raiz;

// // 	while(posicao != NULL) {
// // 		if(valor == posicao->dado) {
// // 			//elemento possui dois filhos
// //             if(posicao->esq != NULL && posicao->dir != NULL) { 
// //     			posicao->dado = maior_elemento_rb(posicao->esq);   
// // 	    		remover_rb(posicao->dado, &(posicao->esq));
// //                 break;
// //             }

// // 			//O elemento possui apenas um filho (direito)
// // 			if(posicao->esq == NULL && posicao->dir != NULL) {
// //                 //O seu filho direito sobe para a posição do elemento  a ser removido
// // 				//e recebe a cor preta
// // 				posicao->dir->cor = PRETO;
// //                 posicao->dir->pai = posicao->pai;

// // 				if(eh_raiz(posicao)) {
// // 					*raiz = posicao->dir;
// // 				} else {
// // 					if(eh_filho_esquerdo(posicao)) {
// //     					posicao->pai->esq = posicao->dir;
// // 					} else {
// // 						posicao->pai->dir = posicao->dir;
// //     				}      
// // 				}
// //                 free(posicao);   
// // 				break;
// // 			}


// // 			//O elemento possui apenas um filho (esquerdo)
// // 			if(posicao->dir == NULL && posicao->esq != NULL) {
// // 				posicao->esq->cor = PRETO;
// // 				posicao->esq->pai = posicao->pai;

// // 				if(eh_raiz(posicao)) {
// // 					*raiz = posicao->esq;
// // 				} else {
// // 					if(eh_filho_esquerdo(posicao)) {
// //     					posicao->pai->esq = posicao->esq;
// // 					} else {
// // 						posicao->pai->dir = posicao->esq;
// //     				}      
// // 				}
// //                 free(posicao);   
// // 				break;
// // 			}

// // 			//O elemento não possui filhos
// // 			if(posicao->esq == NULL && posicao->dir == NULL) {
// // 				//Remover raiz sem filhos					
// // 				if(eh_raiz(posicao)) {
// // 					*raiz = NULL;
// //                     free(posicao);
// // 					break;
// // 				}

// // 				//Remover elemento que não possui filhos e não é raiz
// // 				//Se for vermelho, apenas remove atualizando o ponteiro 
// // 				//correspondente do pai
// // 				if(posicao->cor == VERMELHO) {
// // 					if(eh_filho_esquerdo(posicao))
// // 						posicao->pai->esq = NULL;
// // 					else
// // 						posicao->pai->dir = NULL;
// //                     free(posicao);
// // 					break;
// // 				} else {
// // 					//Se o elemento for preto, substitui pelo duplo preto e depois ajusta
// // 					//a árvore
// // 					no_null->cor = DUPLO_PRETO;
// // 					no_null->pai = posicao->pai;
// // 					if(eh_filho_esquerdo(posicao))
// // 						posicao->pai->esq = no_null;
// // 					else
// // 						posicao->pai->dir = no_null;
// // 					free(posicao);
// // 					reajustar(raiz, no_null);
// // 					break;
// // 				}
// // 			}
// // 		}	
// // 		if(valor > posicao->dado) 
// // 				posicao = posicao->dir;
// // 		else 
// // 				posicao = posicao->esq;
// // 	}
// // }

// /*Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, 
// ou seja, elimina o nó null o duplo-preto.*/
// void reajustar(arvore_rb *raiz, arvore_rb elemento){

// 	//caso 1	
// 	if(eh_raiz(elemento)) {

// 		elemento->cor = PRETO;
//         if(elemento == no_null) {
//             *raiz = NULL;
// 		}
// 		return;
// 	}

// 	//caso 2
// 	if(  cor(elemento->pai) == PRETO &&
// 		 cor(irmao(elemento)) == VERMELHO &&
// 		 cor(irmao(elemento)->dir) == PRETO &&
// 		 cor(irmao(elemento)->esq) == PRETO ) {
//                 //Verifica se é o caso 2 esquerdo ou direito
// 				if(eh_filho_esquerdo(elemento))
// 						rotacao_simples_esquerda_rb(raiz, elemento->pai);
// 				else
// 						rotacao_simples_direita_rb(raiz, elemento->pai);	
				
//                 elemento->pai->pai->cor = PRETO;
// 				elemento->pai->cor = VERMELHO;
				
//                 //Atenção à chamada recursiva do reajustar.
//                 //O caso 2 não remove o duplo-preto
//                 reajustar(raiz, elemento);
// 				return;
// 	}

// 	//caso 3
// 	if(cor(elemento->pai) == PRETO &&
// 	   cor(irmao(elemento)) == PRETO &&
// 	   cor(irmao(elemento)->dir) == PRETO &&
// 	   cor(irmao(elemento)->esq) == PRETO ) {

// 			//Verificar e remover o no_null
// 			elemento->pai->cor = DUPLO_PRETO;
// 			irmao(elemento)->cor = VERMELHO;
			
// 			arvore_rb pai = elemento->pai;
// 			retira_duplo_preto(raiz, elemento);
			
// 			//Chamada recursiva para eliminar o duplo preto do elemento P
// 			//reajustar(raiz, elemento->pai);
// 			reajustar(raiz, pai);
// 			return ;
// 	}	

// 	//caso 4
// 	if(cor(elemento->pai) == VERMELHO &&
// 	   cor(irmao(elemento)) == PRETO &&
// 	   cor(irmao(elemento)->dir) == PRETO &&
// 	   cor(irmao(elemento)->esq) == PRETO ) {	

// 			//Verificar e remover o no_null
// 			elemento->pai->cor = PRETO;
// 			irmao(elemento)->cor = VERMELHO;

// 			retira_duplo_preto(raiz, elemento);
			
// 			return;
// 	}

//     //Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
// 	//caso 5a
// 	if(eh_filho_esquerdo(elemento) &&
// 	   cor(irmao(elemento)) == PRETO &&
// 	   cor(irmao(elemento)->dir) == PRETO &&
// 	   cor(irmao(elemento)->esq) ==VERMELHO) {	

// 			rotacao_simples_direita_rb(raiz, irmao(elemento));
// 			recolorir(irmao(elemento));
// 			if(irmao(elemento)->esq != NULL)
// 				irmao(elemento)->esq->cor = PRETO;

// 			reajustar(raiz, elemento);
// 			return;
// 	}

// 	//caso 5b
// 	if(!eh_filho_esquerdo(elemento) &&
// 	    cor(irmao(elemento)) == PRETO &&
// 	    cor(irmao(elemento)->dir) == VERMELHO &&
// 	    cor(irmao(elemento)->esq) == PRETO) {	

// 			rotacao_simples_esquerda_rb(raiz, irmao(elemento));
// 			recolorir(irmao(elemento));
// 			if(irmao(elemento)->dir != NULL)
// 				irmao(elemento)->dir->cor = PRETO; 

// 			reajustar(raiz, elemento);
// 			return;
// 	}

// 	//caso 6a
// 	if(eh_filho_esquerdo(elemento) &&
// 	   cor(irmao(elemento)) == PRETO &&
// 	   cor(irmao(elemento)->dir) == VERMELHO) {	

// 			irmao(elemento)->cor = elemento->pai->cor;
// 			elemento->pai->cor = PRETO;
// 			irmao(elemento)->dir->cor = PRETO;

// 			rotacao_simples_esquerda_rb(raiz, elemento->pai);
// 			retira_duplo_preto(raiz, elemento);

// 			return;
// 	}

// 	//caso 6b
// 	if(!eh_filho_esquerdo(elemento) &&
// 	    cor(irmao(elemento)) == PRETO &&
// 	    cor(irmao(elemento)->esq) == VERMELHO) {	

// 			irmao(elemento)->cor = elemento->pai->cor;
// 			elemento->pai->cor = PRETO;
// 			irmao(elemento)->esq->cor = PRETO;

// 			rotacao_simples_direita_rb(raiz, elemento->pai);
// 			retira_duplo_preto(raiz, elemento);

// 			return;
// 	}
// }

// void retira_duplo_preto(arvore_rb *raiz, arvore_rb elemento) {
// 			if(elemento == no_null)
// 				if(eh_filho_esquerdo(elemento))
// 						elemento->pai->esq = NULL;
// 				else
// 						elemento->pai->dir = NULL;
// 			else
// 				elemento->cor = PRETO;
// }


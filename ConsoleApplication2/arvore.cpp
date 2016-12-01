#include "arvore.h"
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>

void iniciar(struct NoArvore **raiz)
{
	*raiz = 0;
}

void inserir(int valor, struct NoArvore **raiz)
{
	struct NoArvore *aux = (struct NoArvore*)malloc(sizeof(struct NoArvore));
	aux->info = valor;
	aux->esq = 0;
	aux->dir = 0;
	if (*raiz == 0) *raiz = aux;
	else {
		struct NoArvore *aux2 = *raiz;
		while (aux2 != 0) {
			if (aux->info > aux2->info)
				if (aux2->dir == 0) {
					aux2->dir = aux;
					aux2 = 0;
				}
				else aux2 = aux2->dir;
			else {
				if (aux2->esq == 0) {
					aux2->esq = aux;
					aux2 = 0;
				}
				else aux2 = aux2->esq;
			}
		}
	}
}

bool remover(int valor, struct NoArvore **raiz)
{
	//procura e guarda informação a remover
	struct NoArvore *aux = *raiz;
	//procura e guarda informação do nó pai (ou busca o menor valor no nó da direita no caso 2 de remoção)
	struct NoArvore *aux2 = NULL;
	//guarda a origem do nó filho (esquerda ou direita) do pai
	bool isRight = true;

	while (aux != NULL) {
		//Se encontrou valor
		if (aux->info == valor) {

			//se não houver filhos (raiz checked)
			if (aux->dir == NULL && aux->esq == NULL) {
				aux2 = NULL;
				free(aux);
				return true;
			}

			 //Se houver dois filhos (raiz checked)
			else if (aux->dir != NULL && aux->esq != NULL) {
				aux2 = aux->dir;
				struct NoArvore * smallestValue = aux2;

				while (aux2 != NULL) {
					if (aux2->info < smallestValue->info) {
						smallestValue = aux2;
					}
					aux2 = aux->esq;
				}

				aux->info = smallestValue->info;
				free(smallestValue);
				return true;
			}

			//Se houver apenas um filho (raiz fixed)
			else if (aux->dir != NULL || aux->esq != NULL) {
				if (aux->dir != NULL && aux2 != NULL) {
					if (isRight)
						aux2->dir = aux->dir;
					else
						aux2->esq = aux->dir;
				}
				else if (aux->esq != NULL && aux2 != NULL){
					if (isRight)
						aux2->dir = aux->esq;
					else
						aux2->esq = aux->esq;
				}
				else {
					if (aux->dir != NULL)
						*raiz = aux->dir;
					else
						*raiz = aux->esq;
				}
				free(aux);
				return true;
			}
		}

		//Se o valor procurado for maior do que o atual
		if (aux->info < valor) {
			isRight = true;
			aux2 = aux;
			aux = aux->dir;
		}

		//se o valor atual for menor ou igual ao atual
		else {
			isRight = false;
			aux2 = aux;
			aux = aux->esq;
		}
	}
	return false;
}

int * buscar(int valor, struct NoArvore *raiz, int * cont) {
	//1 - Esquerda
	//2 - Direita
	//0 - Raiz
	//Ponteiro nulo - Erro

	int * elem = 0;
	*cont = 0;

	if (valor == raiz->info) {
		elem = (int *)malloc(sizeof(int));
		(*elem) = 0;
		return elem;
	}
		

	struct NoArvore *aux = raiz;
	while (aux != 0) {
		if (aux->info < valor) {
			elem = (int*)realloc(elem, sizeof(int) * (*cont+1));
			elem[(*cont)] = 2;
			(*cont)++;
			aux = aux->dir;
		}
		else {
			elem = (int*)realloc(elem, sizeof(int) * (*cont+1));
			elem[(*cont)] = 1;
			(*cont)++;
			aux = aux->esq;
		}
		
		if (aux == NULL)
			continue;

		if (aux->info == valor) {
			return elem;
		}
		
	}
	return NULL;
}

//Listagem de números por vetor (erro!)
/*
void listarPre(struct NoArvore * raiz, int * qtde, int * lista) {
	//1 - Adiciona a lista
	//2 - Adiciona o nó a esquerda (se houver)
	//3 - Adiciona o nó a direita (se houver)
	// NÃO SE ESQUEÇA DE ZERAR AS VARIAVEIS AO IMPRIMIR NOVAMENTE A LISTA!
	if (raiz == NULL)
		return;

	lista = (int *)realloc(lista, sizeof(int)* ((*qtde)+1));
	lista[*qtde] = raiz->info;
	qtde++;

	listarPre(raiz->esq,qtde,lista);

	listarPre(raiz->dir,qtde,lista);
}

void listarIn(struct NoArvore * raiz, int * qtde, int * lista) {
	//1 - Adiciona o nó a esquerda (se houver)
	//2 - Adiciona a lista
	//3 - Adiciona o nó a direita (se houver)
	// NÃO SE ESQUEÇA DE ZERAR AS VARIAVEIS AO IMPRIMIR NOVAMENTE A LISTA!
	if (raiz == NULL)
		return;

	listarPre(raiz->esq, qtde, lista);

	lista = (int *)realloc(lista, sizeof(int)* ((*qtde) + 1));
	lista[*qtde] = raiz->info;
	qtde++;

	listarPre(raiz->dir, qtde, lista);
}

void listarPos(struct NoArvore * raiz, int * qtde, int * lista) {
	//1 - Adiciona o nó a esquerda (se houver)
	//2 - Adiciona o nó a direita (se houver)
	//3 - Adiciona a lista
	// NÃO SE ESQUEÇA DE ZERAR AS VARIAVEIS AO IMPRIMIR NOVAMENTE A LISTA!
	if (raiz == NULL)
		return;

	listarPre(raiz->esq, qtde, lista);

	listarPre(raiz->dir, qtde, lista);

	lista = (int *)realloc(lista, sizeof(int)* ((*qtde) + 1));
	lista[*qtde] = raiz->info;
	qtde++;
}
*/

void listarPre(struct NoArvore * raiz) {
	//1 - Imprime
	//2 - Adiciona o nó a esquerda (se houver)
	//3 - Adiciona o nó a direita (se houver)
	// NÃO SE ESQUEÇA DE ZERAR AS VARIAVEIS AO IMPRIMIR NOVAMENTE A LISTA!
	if (raiz == NULL)
		return;

	printf("%d ",raiz->info);

	listarPre(raiz->esq);

	listarPre(raiz->dir);
}

void listarIn(struct NoArvore * raiz) {
	//1 - Adiciona o nó a esquerda (se houver)
	//2 - Imprime
	//3 - Adiciona o nó a direita (se houver)
	// NÃO SE ESQUEÇA DE ZERAR AS VARIAVEIS AO IMPRIMIR NOVAMENTE A LISTA!
	if (raiz == NULL)
		return;

	listarPre(raiz->esq);

	printf("%d ", raiz->info);

	listarPre(raiz->dir);
}

void listarPos(struct NoArvore * raiz) {
	//1 - Adiciona o nó a esquerda (se houver)
	//2 - Adiciona o nó a direita (se houver)
	//3 - Imprime
	// NÃO SE ESQUEÇA DE ZERAR AS VARIAVEIS AO IMPRIMIR NOVAMENTE A LISTA!
	if (raiz == NULL)
		return;

	listarPre(raiz->esq);

	listarPre(raiz->dir);

	printf("%d ", raiz->info);
}

bool AVL(struct NoArvore ** raiz) {
	//Se os filhos da raiz forem nulos então nem continua
	if ((*raiz)->dir == NULL && (*raiz)->esq == NULL) {
		return false;
	}

	//fator de balanceamento = (altura do nó esquerdo) - (altura do nó direito)
	int fator = height((*raiz)->esq) - height((*raiz)->dir);

	struct NoArvore *aux;
	struct NoArvore *aux2;
	struct NoArvore *aux3;
	struct NoArvore *aux4;

	//Se a altura do nó esquerdo for maior
	if (fator > 1) {
		aux = (*raiz)->esq;
		aux3 = (*raiz);
		while (aux != NULL) {
			//rotação direita
			if (aux->esq != NULL && aux->esq->esq != NULL && aux->esq->dir == NULL) {
				aux2 = aux->esq;
				aux3->esq = aux2;
				aux2->dir = aux;
				aux->esq = NULL;
				return true;
			}
			//rotação esquerda
			else if (aux->dir != NULL && aux->dir->dir != NULL && aux->dir->esq == NULL) {
				aux2 = aux->dir;
				aux3->esq = aux2;
				aux2->esq = aux;
				aux->dir = NULL;
				return true;
			}
			//rotação esquerda-direita
			else if (aux->esq != NULL && aux->esq->dir != NULL && aux->esq->dir->esq == NULL && aux->esq->dir->dir == NULL) {
				aux2 = aux->esq;
				aux4 = aux->esq->dir;
				aux->esq = aux4;
				aux4->esq = aux2;
				aux3->esq = aux4;
				aux4->dir = aux;
				aux->esq = NULL;
				aux2->dir = NULL;
				return true;
			}
			//rotação direita-esquerda
			else if (aux->dir != NULL && aux->dir->esq != NULL && aux->dir->esq->esq == NULL && aux->dir->esq->dir == NULL) {
				aux2 = aux->dir;
				aux4 = aux->dir->esq;
				aux->dir = aux4;
				aux4->dir = aux2;
				aux3->esq = aux4;
				aux4->esq = aux;
				aux->dir = NULL;
				aux2->esq = NULL;
				return true;
			}
			//Se falhar, tentar com o próximo nó da esquerda
			else {
				aux = aux->esq;
				aux3 = aux3->esq;
			}
		}
	}

	//Se a altura do nó direito for maior
	else if (fator < -1) {
		aux = (*raiz)->dir;
		aux3 = (*raiz);
		while (aux != NULL) {
			//rotação direita
			if (aux->esq != NULL && aux->esq->esq != NULL && aux->esq->dir == NULL) {
				aux2 = aux->esq;
				aux3->esq = aux2;
				aux2->dir = aux;
				aux->esq = NULL;
				return true;
			}
			//rotação esquerda
			else if (aux->dir != NULL && aux->dir->dir != NULL && aux->dir->esq == NULL) {
				aux2 = aux->dir;
				aux3->esq = aux2;
				aux2->esq = aux;
				aux->dir = NULL;
				return true;
			}
			//rotação esquerda-direita
			else if (aux->esq != NULL && aux->esq->dir != NULL && aux->esq->dir->esq == NULL && aux->esq->dir->dir == NULL) {
				aux2 = aux->esq;
				aux4 = aux->esq->dir;
				aux->esq = aux4;
				aux4->esq = aux2;
				aux3->esq = aux4;
				aux4->dir = aux;
				aux->esq = NULL;
				aux2->dir = NULL;
				return true;
			}
			//rotação direita-esquerda
			else if (aux->dir != NULL && aux->dir->esq != NULL && aux->dir->esq->esq == NULL && aux->dir->esq->dir == NULL) {
				aux2 = aux->dir;
				aux4 = aux->dir->esq;
				aux->dir = aux4;
				aux4->dir = aux2;
				aux3->esq = aux4;
				aux4->esq = aux;
				aux->dir = NULL;
				aux2->esq = NULL;
				return true;
			}
			//se falhar, tentar com o próximo nó da direita
			else {
				aux = aux->dir;
				aux3 = aux3->dir;
			}
		}
	}
	
	//Se a altura estiver ok ou não conseguir balancear
	return false;
}

int height(struct NoArvore * raiz) {
	//Se nó for nulo retorna -1
	if (raiz == NULL) {
		return -1;
	}

	//verifica a altura dos nós seguintes recursivamente
	int esqh = height(raiz->esq);
	int dirh = height(raiz->dir);

	//retorna altura obtida + ajuste dos nós inválidos;
	if (esqh > dirh)
		return (esqh + 1);
	else
		return (dirh + 1);
	
}
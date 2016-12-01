#ifndef BARVORE_H
#define BARVORE_H

struct NoArvore
{
	int info;
	struct NoArvore *esq, *dir;
};

void iniciar(struct NoArvore ** raiz);
void inserir(int valor, struct NoArvore ** raiz);
bool remover(int valor, struct NoArvore ** raiz);
int * buscar(int valor, struct NoArvore * raiz, int * cont);
//Listagem por método de vetores (erro!)
/*
void listarPre(struct NoArvore * raiz,int * qtde, int * lista);
void listarIn(struct NoArvore * raiz, int * qtde, int * lista);
void listarPos(struct NoArvore * raiz, int * qtde, int * lista);
*/
void listarPre(struct NoArvore * raiz);
void listarIn(struct NoArvore * raiz);
void listarPos(struct NoArvore * raiz);
bool AVL(struct NoArvore ** raiz);
int height(struct NoArvore * raiz);

#endif
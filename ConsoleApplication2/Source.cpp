#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "arvore.h"

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Portuguese");
	/*
	if (argc != 2) {
		printf("Uso: %s Arquivo de texto\n",argv[0]);
	}

	else {
	*/
		char cmd[100];
		char args[100];
		int numero;
		//FILE * arq = fopen(argv[1], "r");
		FILE * arq = fopen("C:\\Users\\gabri\\Desktop\\Positivo\\Programa��o II\\4 bimestre\\arvore\\Debug\\coisas.txt", "r");

		if (arq == 0)
			printf("Erro ao abrir o arquivo\n");
		else {
			int x;

			NoArvore *raiz;
			iniciar(&raiz);

			//Enquanto n�o chegar no fim do arquivo
			while ((x = fgetc(arq)) != EOF) {
				fscanf(arq,"%s %s", &cmd,&args);

				//Adicionar n�mero
				if (strcmp(cmd, "add") == 0 || strcmp(cmd, "dd") == 0) {
					//fscanf(arq,"%d\n",&numero);
					numero = strtol(args,NULL, 10);
					inserir(numero, &raiz);
				}

				//Remover n�mero
				else if (strcmp(cmd, "rm") == 0) {
					//fscanf(arq, "%d\n", &numero);
					numero = strtol(args, NULL, 10);
					if (!remover(numero, &raiz))
						printf("%d n�o encontrado\n",numero);
				}

				//Listar �rvore por vetor (com erro!)
				/*
				else if (strcmp(cmd, "print") == 0) {
					int quantidade = 0;
					int * lista = (int*)malloc(0);

					//fscanf(arq, "%s\n", &args);

					if (strcmp(args, "-pre-order") == 0) {
						listarPre(raiz, &quantidade, lista);
						for (int i = 0; i < quantidade; i++)
							printf("%d ",lista[i]);
						printf("\n");
						free(lista);
						quantidade = 0;
					}
					else if (strcmp(args, "-in-order") == 0) {
						listarIn(raiz, &quantidade, lista);
						for (int i = 0; i < quantidade; i++)
							printf("%d ", lista[i]);
						printf("\n");
						free(lista);
						quantidade = 0;
					}
					else if (strcmp(args, "-post-order") == 0) {
						listarPos(raiz, &quantidade, lista);
						for (int i = 0; i < quantidade; i++)
							printf("%d ", lista[i]);
						printf("\n");
						free(lista);
						quantidade = 0;
					}
					else {
						printf("Comando inv�lido, pulando.\n");
						continue;
					}
				}
				*/

				//Listar �rvore
				else if (strcmp(cmd, "print") == 0) {
					
					//fscanf(arq, "%s\n", &args);

					if (strcmp(args, "-pre-order") == 0) {
						listarPre(raiz);
						printf("\n");
					}
					else if (strcmp(args, "-in-order") == 0) {
						listarIn(raiz);
						printf("\n");
					}
					else if (strcmp(args, "-post-order") == 0) {
						listarPos(raiz);
						printf("\n");
					}
					else {
						printf("Comando inv�lido, pulando.\n");
						continue;
					}
				}

				//Procurar n�mero
				else if (strcmp(cmd, "find") == 0) {
					int contador = 0;
					int * posicao;
					int esqCont = 0;
					int dirCont = 0;
					//int acumulador = 0;
					//bool isLeft;

					//gera o vetor posi��o do n�mero
					//fscanf(arq, "%d\n", &numero);
					numero = strtol(args, NULL, 10);

					posicao = buscar(numero, raiz, &contador);

					//se ponteiro for nulo o valor n�o foi encontrado
					if (posicao == 0) {
						printf("%d - n�o encontrado\n", numero);
						continue;
					}

					//se o primeiro valor for 0 o n�mero est� na raiz
					if (posicao[0] == 0) {
						printf("%d - n� raiz\n", numero);
						continue;
					}

					printf("%d - ",numero);
					//conta e gera as posi��es a imprimir (old)
					/*
					for (int i = 0; i < contador; i++) {
						//esquerda
						if (posicao[i] == 1) {
							if (acumulador == 0) {
								acumulador++;
								isLeft = true;
								continue;
							}

							if (isLeft) {
								acumulador++;
								if (i == (contador - 1)) {
									printf("%d n�(s) � esquerda ", acumulador);
								}
							}
							else {
								printf("%d n�(s) � direita ", acumulador);
								acumulador = 1;
								isLeft = true;
							}
						}

						//direita
						else {
							if (acumulador == 0) {
								acumulador++;
								isLeft = false;
								continue;
							}

							if (!isLeft) {
								acumulador++;
								if (i == (contador - 1)) {
									printf("%d n�(s) � direita ", acumulador);
								}
							}
							else {
								printf("%d n�(s) � esquerda ", acumulador);
								acumulador = 1;
								isLeft = false;
							}
						}
					}
				*/

					for (int i = 0; i < contador; i++) {
						if (posicao[i] == 1) {
							esqCont++;
							if (i == contador - 1 || posicao[i+1] != 1) {
								printf("%d n�(s) � esquerda ",esqCont);
								esqCont = 0;
							}
						}
						else if (posicao[i] == 2) {
							dirCont++;
							if (i == contador - 1 || posicao[i + 1] != 2) {
								printf("%d n�(s) � direita ", dirCont);
								dirCont = 0;
							}
						}
					}

					//limpa as vari�veis para uma pr�xima inst�ncia do programa
					printf("\n");
					//acumulador = 0;
					esqCont = 0;
					dirCont = 0;
					contador = 0;
					free(posicao);
				}

				//Balancear �rvore (AVL)
				else if (strcmp(cmd, "balance") == 0) {
					AVL(&raiz);
				}

				//Sair do programa (ORLY?)
				else if (strcmp(cmd, "end") == 0) {
					return 0;
				}

				else {
					printf("Comando inv�lido, pulando.\n");
					continue;
				}
			}
		}
	/*
	}
	*/

	return 0;
}
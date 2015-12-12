#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct threadArg{
	int combInicial;
	int combFinal;
	int* calorias;
	int qtdeAlimentos;
	int soma;
	int* solucaoEncontrada;
} threadArg;

void comb(int* conjunto, int* v, int srcIndex, int vIndex, int qtdeAlimentos, int vSize, int consumo, int *flagEncontrado);
void genComb(int* calorias, int qtdeAlimentos, int k, int consumo, int *flagEncontrado);
int verificaSolucao(int* calorias, int qtdeAlimentos, int soma, int qtdeThreads);
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	// ID do quarteirão
	int node; 
	// Probabilidade de não ter incêndio do quarteirão de origem até node
	double prob; 
} Item;

typedef struct {
	Item *v;
	int size;
} Heap;

void inicializaHeap(Heap *h, int n);
void insereItem(Heap *h, Item i, int *pos);
void RefazBaixoCima(Item A[], int k, int *pos);
void RefazCimaBaixo(Item A[], int k, int Dir, int *pos);
void constroiHeap(Heap *h, int *pos);
Item topo(Heap *h);
void retiraHeap(Heap *h, int *pos);

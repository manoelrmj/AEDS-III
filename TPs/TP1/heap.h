#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Item;

typedef struct {
	Item *v;
	int size;
} Heap;

void inicializaHeap(Heap *h, int n);
void insereItem(Heap *h, Item i);
void RefazBaixoCima(Item A[], int k);
void RefazCimaBaixo(Item A[], int k, int Dir);
void constroiHeap(Heap *h);

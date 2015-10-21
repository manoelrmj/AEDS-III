#include "heap.h"

void inicializaHeap(Heap *h, int n){
	int i;
	h->v = (Item*) malloc(n+1*sizeof(Item));
	for(i=0; i<n+1; i++)
		h->v[i].prob = -1;
	h->size = 1;
}

void insereItem(Heap *h, Item i, int *pos){
	h->v[h->size] = i;
	pos[i.node] = h->size;
	h->size++;
	RefazBaixoCima(h->v, h->size, pos); // ALTEREI AQUI
}

void Troca(Item *A, Item *B, int *pos){
	Item aux = *A;
	int posAux = pos[A->node];
	pos[A->node] = pos[B->node];
	pos[B->node] = posAux;
	*A = *B;
	*B = aux;
}

void RefazBaixoCima(Item A[], int k, int *pos) {
	/* se pai for menor que filho, troca */
	while (k > 1 && A[k/2].prob < A[k].prob) {
		Troca(&A[k], &A[k/2], pos);
		/* vai para o pai e repete o processo */
		k = k / 2;
	}
}

void RefazCimaBaixo(Item A[], int k, int Dir, int *pos) {
	int j;
 	while (2*k <= Dir) {
 		j = 2*k;
 		/* encontra maior filho */
 		if (j < Dir && A[j].prob < A[j+1].prob)
 			j++;
 		/* testa se pai é maior que filho */
 		if (A[k].prob >= A[j].prob)
 			break;
 		/* pai é menor que filho, troca posições */
 		Troca(&A[k], &A[j], pos);
 		k = j;
 	}
}

void constroiHeap(Heap *h, int *pos) {
	int Esq;
	/* inicia na metade do vetor */
	Esq = h->size / 2 + 1;
	while (Esq > 1) {
		Esq--;
		RefazCimaBaixo(h->v, Esq, h->size, pos);
	}
}

Item topo(Heap *h){
	return h->v[1];
}

void retiraHeap(Heap *h, int *pos){
	h->v[1] = h->v[h->size - 1];
	h->size--;
	constroiHeap(h, pos);
}
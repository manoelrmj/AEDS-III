#include "heap.h"

void inicializaHeap(Heap *h, int n){
	h->v = (Item*) malloc(n*sizeof(Item));
	h->size = 1;
}

void insereItem(Heap *h, Item i){
	h->v[h->size] = i;
	h->size++;
}

void Troca(Item *A, Item *B){
	Item aux = *A;
	*A = *B;
	*B = aux;
}

void RefazBaixoCima(Item A[], int k) {
	/* se pai for menor que filho, troca */
	while (k > 1 && A[k/2] < A[k]) {
		Troca(&A[k], &A[k/2]);
		/* vai para o pai e repete o processo */
		k = k / 2;
	}
}

void RefazCimaBaixo(Item A[], int k, int Dir) {
	int j;
 	while (2*k <= Dir) {
 		j = 2*k;
 		/* encontra maior filho */
 		if (j < Dir && A[j] < A[j+1])
 			j++;
 		/* testa se pai é maior que filho */
 		if (A[k] >= A[j])
 			break;
 		/* pai é menor que filho, troca posições */
 		Troca(&A[k], &A[j]);
 		k = j;
 	}
}

void constroiHeap(Heap *h) {
	int Esq;
	/* inicia na metade do vetor */
	Esq = h->size / 2 + 1;
	while (Esq > 1) {
		Esq--;
		RefazCimaBaixo(h->v, Esq, h->size);
	}
}
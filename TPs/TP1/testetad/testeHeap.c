#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void main(){
	Item it[10];	
	int *position = malloc(10*sizeof(int));
	int i;
	for(i=0; i<10; i++){
		it[i].node = i;
		it[i].prob = (rand()%100);
		position[i] = -1;
	}
	/*** POSICAO ***/
	printf("\nPOS: ");
	for(i=0; i<10; i++)
		printf("[%d] -> %d   ", i, position[i]);	
	/*** POSICAO ***/
	printf("\nBFR HEAP:\n");
	for(i=0; i<10; i++)
		printf("%.1lf  ", it[i].prob);
		
	Heap h;
	inicializaHeap(&h, 10);
	for(i=0; i<10; i++)
		insereItem(&h, it[i], position);
	/*** POSICAO ***/
	printf("\nPOS: ");
	for(i=0; i<10; i++)
		printf("[%d] -> %d   ", i, position[i]);	
	/*** POSICAO ***/	
	constroiHeap(&h, position);
	printf("\nAFT HEAP:\n");
	for(i=1; i<h.size; i++)
		printf("%.1lf  ", h.v[i].prob);
	printf("\n");
	/*** POSICAO ***/
	printf("\nPOS: ");
	for(i=0; i<10; i++)
		printf("[%d] -> %d   ", i, position[i]);	
	/*** POSICAO ***/

	retiraHeap(&h, position);
	printf("\nRetira raíz:\n");
	for(i=1; i<h.size; i++)
		printf("%.1lf  ", h.v[i].prob);
	/*** POSICAO ***/
	printf("\nPOS: ");
	for(i=0; i<10; i++)
		printf("[%d] -> %d   ", i, position[i]);	
	/*** POSICAO ***/
	printf("\n");
	printf("\nTopo: %d|%.1lf\n", topo(&h).node, topo(&h).prob);	
}
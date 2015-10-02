#include <stdio.h>
#include <stdlib.h>

#define MAXVERTICES 200000
#define MAXEDGES 200000

/* Métodos e operações sobre lista de adjacência */
typedef struct edge{
	int vertice;
	int weight;	
} Edge;

typedef struct Cell *pointer;

typedef struct {
	Edge edge;
	pointer next;
} Cell;

typedef struct {
	pointer first, last;
} List;

typedef struct {
	List Adj[MAXVERTICES + 1]; 
	int numVertices;
	int numArestas;
} Graph;

void CEList(List *list){ //CreateEmptyList
	list->first = (pointer) malloc(sizeof(Cell));
	list->last = list->first;
	list->first->next = NULL;
}

int Empty(List *list){ // Check if the list is empty
	return (list->first == list->last);
}

void Insert(Edge item, List *list){ // Insert an item in the list
	list->last->next = malloc(sizeof(Cell)); // Aloca espaço para o novo item
	list->last = list->last->next; // O último elemento passa a ser a nova célula inserida
	list->last->edge = item;
	list->last->next = NULL;
}


void main(){
	int m = -1; // Número de junções de byteland (# vértices)
	int n = -1; // Número de estradas em byteland (# arestas)
	int i;

	while(m && n != 0){
		scanf("%d %d", &m, &n);
					
	}
}
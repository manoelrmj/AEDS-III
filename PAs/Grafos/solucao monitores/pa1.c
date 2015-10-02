#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ESTRUTURAS E FUNÇÕES PARA LISTA ENCADEADA */

typedef struct nodo
{
	int vertice;
	struct nodo* prox;
} Nodo;

typedef struct
{
	Nodo* primeiro;
	Nodo* ultimo;
} Lista;

void inicializa_lista(Lista* l)
{
	l->primeiro = NULL;
	l->ultimo = NULL;
}

void insere(Lista* l, int vertice)
{
	if (l->primeiro == NULL)
	{
		l->primeiro = (Nodo*) malloc(sizeof(Nodo));
		l->primeiro->vertice = vertice;
		l->primeiro->prox = NULL;
		l->ultimo = l->primeiro;
	}
	else
	{
		l->ultimo->prox = (Nodo*) malloc(sizeof(Nodo));
		l->ultimo = l->ultimo->prox;
		l->ultimo->vertice = vertice;
		l->ultimo->prox = NULL;
	}
}

void destroi(Lista* l)
{
	Nodo* atual = l->primeiro;
	while (atual != NULL)
	{
		Nodo* temp = atual->prox;
		free(atual);
		atual = temp;
	}
}

void DFS(unsigned int v, Lista* adj, unsigned int* visitados, unsigned int* contador_passos)
{
	visitados[v] = 1;
	Nodo* atual = adj[v].primeiro;
	while (atual != NULL)
	{
		if (visitados[atual->vertice] == 0)
		{
			(*contador_passos) += 2;
			
			DFS(atual->vertice, adj, visitados, contador_passos);
		}
		atual = atual->prox;
	}
}

int main()
{
	int num_casos;
	scanf("%d\n", &num_casos);

	unsigned int i, j;
	for (i = 0; i < num_casos; ++i)
	{
		int partida;
		scanf("%d\n", &partida);

		int num_vertices, num_arestas;
		scanf("%d %d\n", &num_vertices, &num_arestas);

		Lista adj[num_vertices];
		for (j = 0; j < num_vertices; ++j)
			inicializa_lista(&adj[j]);

		for (j = 0; j < num_arestas; ++j)
		{
			int u, v;
			scanf("%d %d\n", &u, &v);
			insere(&adj[u], v);
			insere(&adj[v], u);
		}

		unsigned int contador_passos = 0;
		unsigned int visitados[num_vertices];
		for (j = 0; j < num_vertices; ++j)
			visitados[j] = 0;
		DFS(partida, adj, visitados, &contador_passos);

		printf("%d\n", contador_passos);
		for (j = 0; j < num_vertices; ++j)
			destroi(&adj[j]);
	}
}

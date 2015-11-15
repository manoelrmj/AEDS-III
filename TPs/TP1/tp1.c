#include "linkedlist.h"
#include "queue.h"
#include "heap.h"
#include <limits.h>
// Valor não possível para probabilidade
#define INFINITY -1  

// Busca em largura
void BFS(int *visited, int *reachable, Set *s, int source, queue *q, int k){
	// Iterador para percorrer os adjacentes do nó
	iterator it; 
	// Insere o primeiro elemento com disância zero
	push(source, 0, q); 
	visited[source] = 1;
	reachable[source] = 1;
	while(!emptyQueue(q) && front(q)->distance < k){		
		for(it=begin(&s[front(q)->key]); it != end(&s[front(q)->key]); it=next(it)){
			if(!visited[it->destination]){
				push(it->destination, front(q)->distance+1, q);
				visited[it->destination] = 1;
				reachable[it->destination] = 1;	
			}			
		}
		pop(q); 
	}
}

// Dijkstra (caminho mínimo)
void Dijkstra(Set *listaAdj, int numVertices, int numArestas, int origem, int destino, int *alcancavel){
	if(!alcancavel[origem]){
		printf("-1\n");
		return;
	}
	// Arrays de probabilidade, antecessores, visitados, posição do heap e caminho final
	double *p = malloc(numVertices*sizeof(double));
	int *Antecessor = malloc(numVertices*sizeof(int));
	int *visitado = calloc(numVertices, sizeof(int));
	int *heapPos = malloc(numVertices*sizeof(int));
	int *path = malloc(numVertices*sizeof(int));
	// Estrutura heap que implementa lista de prioridades
	Heap h;
	inicializaHeap(&h, numVertices);
	int u, i, v;
	iterator it;
	Item auxNode; // auxiliar para inserção no heap
	for(u=0; u<numVertices; u++){
		Antecessor[u] = -1;
		p[u] = INFINITY;		
		heapPos[u] = -1;
	}
		
	int j;
	p[origem] = 1; // Probabilidade de incêndio na origem é nula
	visitado[origem] = 1;
	i = origem;
	while(h.size >= 1){ // Enquanto o heap não estiver vazio
		visitado[i]	= 1;
		for(it=begin(&listaAdj[i]); it!=end(&listaAdj[i]); it=next(it)){
			if(heapPos[it->destination] == -1 && !visitado[it->destination] && alcancavel[it->destination]){
				auxNode.node = it->destination;
				auxNode.prob = p[i] * (1-it->probability);
				insereItem(&h, auxNode, heapPos);
				p[it->destination] = p[i] * (1 - it->probability);
				Antecessor[it->destination] = i;
			}else if(p[it->destination] < p[i] * (1 - it->probability)
				&& !visitado[it->destination] && alcancavel[it->destination]){
				// Relaxamento
				h.v[heapPos[it->destination]].prob = p[i] * (1 - it->probability);
				p[it->destination] = p[i] * (1 - it->probability);
				Antecessor[it->destination] = i;
				constroiHeap(&h, heapPos);
			}
		}
		auxNode = topo(&h);
		i = auxNode.node;
		retiraHeap(&h, heapPos);
	}

	u = 0;
	if(p[destino] == INFINITY){
		printf("%d\n", -1);
	}else{
		// Probabilidade de passar por um incêndio até o destino
		printf("%.2lf", 1-p[destino]); 
		for(j=Antecessor[destino]; (j!=origem); j=Antecessor[j]){
			path[u] = j;
			u++;
		}
		path[u] = origem;
		for(v=u; v>=0; v--)
			printf(" %d", path[v]);
		printf(" %d", destino);
		printf("\n");
	}
	
	// Liberação de memória alocada dinamicamente
	free(p);
	free(Antecessor);
	free(visitado);
	free(heapPos);
	free(path);
	free(h.v);
}

int main(){
	int N; // Número de instâncias do problema
	int Q; // Número de quarteirões
	int R; // Número de ruas
	int S; // Ponto de saída
	int C; // Ponto de chegada
	int K; // Distância máxima à um corpo de bombeiro
	int D; // Número de corpo de bombeiros na cidade
 	// Auxiliares para ler uma rua de 'u' para 'v' com probabilidade 'p'
 	int u, v; 
	float p;
	int d;
	// Arranjo que indica quais quarteirões tem um corpo de bombeiros
	int *fireStation; 	
	Set *listaAdj; // Lista de adjacência
	int *reachable; // Alcançáveis
	int *visited; // Visitados
	int i, j;	

	scanf("%d", &N);
	for(i=0; i<N; i++){ // Leitura das instâncias
		scanf("%d %d %d %d %d %d", &Q, &R, &S, &C, &K, &D);
		// Cria e inicializa a lista de adjacência de cada vértice
		listaAdj = malloc(Q*sizeof(Set));
		for(j=0; j<Q; j++)
			makeSet(&listaAdj[j]);
		
		/* Cria um arranjo de Q posições para indicar quais quarteirões tem um 
		 * corpo de bombeiros. Inicialmente, nenhum quarteirão o possui, até que
		 * seja feita a leitura.
		 */
		fireStation = (int*) calloc(Q, sizeof(int));

		for(j=0; j<R; j++){ // Leitura das ruas
			scanf("%d %d %f", &u, &v, &p);
			insert(v, p, &listaAdj[u]);
			insert(u, p, &listaAdj[v]);
		}

		for(j=0; j<D; j++){ // Leitura dos quarteirões c/ corpo de bombeiros
			scanf("%d", &d);
			fireStation[d] = 1;
		}

		/**** Fim de leitura da instância ****/

		reachable = calloc(Q, sizeof(int));
		visited = calloc(Q, sizeof(int));
		queue q;
		// Inicializa a fila
		makeQueue(&q);
		/* Para cada corpo de bombeiro, determinar os vértices alcançáveis a
		 * partir de uma busca em largura.
		 */ 

		for(j=0; j<Q; j++){
			if(fireStation[j]){
				BFS(visited, reachable, listaAdj, j, &q, K);
				while(!emptyQueue(&q))
					pop(&q);
			}	
		}	
		freeQueue(&q);
		// Operações para o algorítmo de Dijkstra
		Dijkstra(listaAdj, Q, R, S, C, reachable);
		for(j=0; j<Q; j++) 
			freeSet(&listaAdj[j]);
	
		// Libera memória alocada dinamicamente
		free(listaAdj);
		free(fireStation);
		free(reachable);
		free(visited);
	}
	
	return 0;	
}

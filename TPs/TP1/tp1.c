#include "linkedlist.h"
#include "queue.h"
#include "heap.h"
#include <limits.h>
// Valor não possível para probabilidade
#define INFINITY -1  

/* Este método calcula a probabilidade de se passar por um incêndio em um dado
 * caminho. A entrada consiste de uma lista de arestas que representa o caminho
 * a ser percorrido. 
 */
double probability(Set *s){
	iterator it;
	double pn = 1;
	for(it=begin(s); it != end(s); it=next(it)){
		pn *= (1-it->probability);
	}
	return 1 - pn;
}

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
	// Arrays de limite de peso e Antecessores
	double *p = malloc(numVertices*sizeof(double));
	int *Antecessor = malloc(numVertices*sizeof(int));
	int *visitado = malloc(numVertices*sizeof(int));
	int *heapPos = malloc(numVertices*sizeof(int));
	// Estrutura heap que implementa lista de prioridades
	Heap h;
	inicializaHeap(&h, numVertices);
	int u, i;
	iterator it;
	Item auxNode; // auxiliar para inserção no heap
	for(u=0; u<numVertices; u++){
		Antecessor[u] = -1;
		p[u] = INFINITY;
		heapPos[u] = -1;		
	}
	/****TESTE****/
	/*printf("----------\nANT: ");
	for(i=0; i<numVertices; i++)
		printf("%d ", Antecessor[i]);
	printf("\n");
	printf("PRB: ");
	for(i=0; i<numVertices; i++)
		printf("%.2lf ", p[i]);
	printf("\n----------\n");*/
	/****TESTE****/
	int j;
	p[origem] = 1; // Probabilidade de incêndio na origem é nula
	i = origem;
	while(h.size >= 1){ // Enquanto o heap não estiver vazio
		visitado[i]	= 1;
		for(it=begin(&listaAdj[i]); it!=end(&listaAdj[i]); it=next(it)){
			printf("%d , ALC: %d, VIS: %d\n", it->destination, alcancavel[it->destination], visitado[it->destination]);
			if(heapPos[it->destination] == -1 && !visitado[it->destination] && alcancavel[it->destination]){
				auxNode.node = it->destination;
				auxNode.prob = it->probability;
				//printf("Inseri: %d\n", auxNode.node);
				insereItem(&h, auxNode, heapPos);
				p[it->destination] = p[i] * (1 - it->probability);
				Antecessor[it->destination] = i;
			}else if(h.v[heapPos[it->destination]].prob > p[i] * (1 - it->probability)
				&& !visitado[it->destination] && alcancavel[it->destination]){
				// Relaxamento
				//printf("Relaxei %d com %d(%.2lf[%d], %.2lf)\n", it->destination, i, h.v[heapPos[it->destination]].prob, Antecessor[h.v[heapPos[it->destination]].node], p[i] * (1 - it->probability));
				h.v[heapPos[it->destination]].prob = p[i] * (1 - it->probability);
				Antecessor[it->destination] = i;
				constroiHeap(&h, heapPos); // Usar Refaz
			}
		}
		/*for( j = 1; j <= h.size; j++){
			printf("(%d, %.2lf) ", h.v[j].node, h.v[j].prob);
		}
		printf("\n");*/
		auxNode = topo(&h);
		i = auxNode.node;
		//printf("Retirei: %d\n", auxNode.node);
		retiraHeap(&h, heapPos);
	}
	/****** TESTE *******/
	printf("\n\nProb destino: %.2lf", 1-p[destino]);	
	printf("\nAnt[]: ");
	for(j=0; j<numVertices; j++)
		printf("%d ", Antecessor[j]);
	printf("\n");
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
		fireStation = malloc(Q*sizeof(int));
		for(j=0; j<Q; j++)
			fireStation[j] = 0;

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

		int *reachable = malloc(Q*sizeof(int));
		int *visited = malloc(Q*sizeof(int));
		queue q;
		// Inicializa a fila
		makeQueue(&q);
		for(j=0; j<Q; j++){
			reachable[i] = 0;
			visited[i] = 0;
		}
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

		// Operações para o algorítmo de Dijkstra
		Dijkstra(listaAdj, Q, R, S, C, reachable);		
	}
	// Libera memória alocada dinamicamente
	for(j=0; j<Q; j++) 
		freeSet(&listaAdj[j]);
	free(listaAdj);
	free(fireStation); 	
	return 0;	
}

#include "linkedlist.h"
#include "queue.h"

/* Este método calcula a probabilidade de se passar por um incêndio em um dado
 * caminho. A entrada consiste de uma lista de arestas que representa o caminho
 * a ser percorrido. 
 */
float probability(Set *s){
	iterator it;
	float pn = 1;
	for(it=begin(s); it != end(s); it=next(it)){
		pn *= (1-it->probability);
	}
	return 1 - pn;
}

// Busca em largura
void BFS(int *visited, int *reachable, Set *s, int source, queue *q, int k){
	iterator it; // Iterador para percorrer os adjacentes do nó
	push(source, 0, q); // Insere o primeiro elemento com disância zero
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

		int *visited = malloc(Q*sizeof(int));
		int *reachable = malloc(Q*sizeof(int));
		queue q;
		makeQueue(&q);
		for(j=0; j<Q; j++){
			visited[i] = 0;
			reachable[i] = 0;
		}
		for(j=0; j<Q; j++){
			if(fireStation[j]){
				BFS(visited, reachable, listaAdj, j, &q, K);
				while(!emptyQueue(&q))
					pop(&q);
			}	
		}
		for(j=0; j<Q; j++){
			printf("%d ", reachable[j]);
		}
		printf("\n");

	}
	// Libera memória alocada dinamicamente
	for(j=0; j<Q; j++) 
		freeSet(&listaAdj[j]);
	free(listaAdj);
	free(fireStation); 	
	return 0;	
}

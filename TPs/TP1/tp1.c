#include "linkedlist.h"

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
		}

		for(j=0; j<D; j++){ // Leitura dos quarteirões c/ corpo de bombeiros
			scanf("%d", &d);
			fireStation[d] = 1;
		}

		// Teste de probabilidade
		Set path;
		makeSet(&path);
		insert(3, 0.2, &path);
		insert(4, 0.2, &path);
		//insert(1, 0.4, &path);
		printf("PN: %f\n", probability(&path));

		// -- TESTE
		/*int k;
		iterator it;
		printf("Instância %d", i+1);
		for(k=0; k<Q; k++){
			printf("\nLista de adjacência do nó %d ", k);
			if(fireStation[k])
				printf("(corpo de bombeiro presente)\n");
			else
				printf("\n");
			for(it=begin(&listaAdj[k]); it != end(&listaAdj[k]); it = next(it))
				printf(" - dest: %d | peso: %f\n", it->destination, it->probability);			
		}*/		
		// -- TESTE
	}
	// Libera memória alocada dinamicamente
	for(j=0; j<Q; j++) 
		freeSet(&listaAdj[j]);
	free(listaAdj);
	free(fireStation); 	
	return 0;	
}

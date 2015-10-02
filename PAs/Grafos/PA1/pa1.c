#include <stdio.h>
#include <stdlib.h>

int temAdj(int **grafo, int n, int v){
	int i;
	for(i=0; i<n; i++){
		if(grafo[v][i])
			return 1;
	}
	return 0;
}

void VisitaDFS(int **grafo, int v, int n, int *visitado, int *contador){ // grafo/nº de arestas/aresta inicial/vetor que informa se o vértice já foi visitado/local onde será armazenado qtde de movimentos
	int i;
	visitado[n] = 1;
	if(temAdj(grafo, v, n)){
		for(i=0; i<v; i++){
			if(grafo[n][i]){
				if(visitado[i] == 0){
					VisitaDFS(grafo, v, i, visitado, contador);					
				}
				(*contador)++;
			}
		}
	}
}

void main(){
	
	int T; // Quantidade de casos de teste (T<100)
	int N;  // Nodo onde o desenho deve ser iniciado/terminado
	int V, A; // Quantidade de vertices e arestas
	int u, v; // origem/destino de um vértice
	int cont, i, j; // iteradores
	int **matAdj; // matriz de adjacencia
	int movimentos = 0;
	int *visitado;
	
	scanf("%d", &T);
	for(cont=0; cont<T; cont++){
		scanf("%d", &N);
		scanf("%d %d", &V, &A);
		matAdj = calloc(V, sizeof(int*)); //Alocação da matriz
		for(i=0; i<V; i++)
			matAdj[i] = calloc(V, sizeof(int));				
		
		for(j=0; j<A; j++){ // Atribuição das arestas (grafo não direcionado, matriz simétrica)
			scanf("%d %d", &u, &v);			
			matAdj[u][v] = 1;
			matAdj[v][u] = 1;
		}
		visitado = calloc(V, sizeof(int));
		movimentos = 0;
		VisitaDFS(matAdj, V, N, visitado, &movimentos);
		printf("%d\n", movimentos);
		free(matAdj);
		free(visitado);
	}
}
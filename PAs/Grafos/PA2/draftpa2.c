#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y, z;
} Aresta;

/* Esta função compara a aresta 'a' com a 'b' e, se o valor retornado for menor do que 0, então o elemento 'a' é menor. 
 * Se o valor retornado for igual a 0, os elementos são iguais e se for maior do que 0 'b' é maior do que 'a'
 */
int cmp(const void* a, const void* b){
	Aresta A = *(const Aresta*)a;
	Aresta B = *(const Aresta*)b;
	return A.z - B.z;
}

int parent(int u, int *v){
	if(v[u] == u)
		return u;
	else
		return parent(v[u], v);
}

void main(){
	int m = -1; // Número de junções de byteland (# vértices)
	int n = -1; // Número de estradas em byteland (# arestas)
	int i, j, aux;
	int cont, custoTotal, custoOtimo;
	Aresta *arrayArestas;
	while(1){
		scanf("%d %d", &m, &n);
		if(m == 0 && n == 0)
			break;		
		// Zera as variáveis a cada entrada
		cont = 0;
		custoTotal = 0;
		custoOtimo = 0;
		// Cria o vetor de arestas 
		arrayArestas = (Aresta*) malloc(n*sizeof(Aresta));
		// Preenche o vetor de aresta com as entradas (x:origem, y:destino, z:peso)
		for(i=0; i<n; i++)
			scanf("%d %d %d", &arrayArestas[i].x, &arrayArestas[i].y, &arrayArestas[i].z);
				
		// Ordena os elementos conforme o peso (do menor p/ o maior caminho)
		qsort(arrayArestas, n, sizeof(Aresta), cmp);	
		for(i=0;i<n;i++)
			printf("%d %d %d\n", arrayArestas[i].x, arrayArestas[i].y, arrayArestas[i].z);
		printf("\n\n");

		// Calcula o custo total do grafo
		for(i=0; i<n; i++)
			custoTotal += arrayArestas[i].z;
		
		int vertices[m];
		for(i=0; i<m; i++)
			vertices[i] = i;
		// -- remove
		for(i=0; i<m; i++)
			printf("%d ", vertices[i]);
		printf("\n");
		// -- remove

		for(i=0; i<n; i++){
			int origem = arrayArestas[i].x;
			int destino = arrayArestas[i].y;
			if(parent(origem, vertices) != parent(destino, vertices)){// Só adiciona a aresta caso o vértice sendo analisado ainda não consegue ser alcançado pelo nó raiz
				//vertices[parent(origem, vertices)] = vertices[parent(destino, vertices)];
				vertices[parent(destino, vertices)] = vertices[parent(origem, vertices)];
				// -- remove
				for(j=0; j<m; j++)
					printf("%d ", vertices[j]);
				printf("\n");
				// -- remove
				cont++; // Conta o número de arestas adicionadas à AGM
				custoOtimo += arrayArestas[i].z; 
			} 
			if(cont == m-1) // Se o número de arestas adicionadas for igual ao número de vértices-1, todos os vértices já estarão conectados
				break;			
		}
		printf("%d\n", custoTotal-custoOtimo);
		free(arrayArestas);			
	}
}
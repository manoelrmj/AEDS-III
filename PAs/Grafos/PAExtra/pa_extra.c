#include <stdio.h>
#include <stdlib.h>

// Cada célula da lista contem o vertice destino e os apontadores necessários
typedef struct vertice{
	int adjacente;
	struct vertice *prev;
	struct vertice *next;
} Vertice;

typedef Vertice *iterator;

// Lista de palavras
typedef struct {
	Vertice *end; // Sentinela da lista
	int size;
} Set;

void makeSet(Set *s){
	s->size = 0;
	s->end = malloc(sizeof(Vertice));
	s->end->adjacente = -1;
	s->end->next = s->end;
	s->end->prev = s->end;	
}

iterator begin(Set *s){
	return s->end->next;
}

iterator end(Set *s){
	return s->end;	
}

iterator next(iterator x){
	return x->next;
}

iterator prev(iterator x){
	return x->prev;
}

int empty(Set *s){
	return s->size == 0;
}

int key(iterator x){
	return x->adjacente;
}

iterator find(int k, Set *s){
	iterator i;
	for(i = begin(s); i != end(s); i = next(i)){
		if(key(i) == k)
			return i;		
	}
	return end(s); // Busca sem sucesso
}

void insert(int k, Set *s){
	iterator a = find(k, s);
	if(a == end(s)){ // Se o anagrama não existir na lista, inseri-lo
		Vertice *v = malloc(sizeof(Vertice));
		v->adjacente = k;
		v->prev = end(s)->prev;
		v->prev->next = v;
		v->next = end(s);
		end(s)->prev = v;
		s->size++;
	}
}

void erase(int k, Set *s){
	Vertice *v = find(k, s);
	if(v != end(s)){ // Se o anagrama exisitr
		v->prev->next = v->next;
		v->next->prev = v->prev;
		free(v);
		s->size--;
	}
}

void clear(Set *s){
	while(!empty(s))
		erase(key(begin(s)), s);
}

void freeSet(Set *s){
	clear(s);
	free(s->end);
}

int VisitaDFS(Set *listaAdj, int v, char *cor, int *loop){ // grafo/aresta inicial/vetor de cores/flag de loop
	iterator it;
	cor[v] = 'C';
	if(listaAdj[v].size !=0){
		for(it=begin(&listaAdj[v]); it != end(&listaAdj[v]); it = next(it)){
			if(cor[key(it)] == 'B'){
				VisitaDFS(listaAdj, key(it), cor, loop);					
			}else if(cor[key(it)] == 'C'){ // Caso o nó seja cinza, este está sendo visitado, o que caracteriza uma aresta de retorno e, portanto, um loop.
				*(loop) = 1;
			}			
		}		
	}
	cor[v] = 'P';	
}

void verificaCiclo(Set *listaAdj, int N, int *loop){
	char* cor;
	int i;
	cor = malloc(N*sizeof(char));
	for(i=0; i < N; i++)
		cor[i] = 'B';
	for(i=0; i < N; i++){
		if(cor[i] == 'B')
			VisitaDFS(listaAdj, i, cor, loop);
	}
	free(cor);
}

int main(){
	int T; // Qtde de casos de teste (T<100)
	int N; // Qtde de documentos (vertices)
	int M; // Qtde de dependencias (arestas)
	int i, j;
	int u = 0;
	int v = 0;
	int loop;
	Set *listaAdj; // Cada vértice terá uma lista
	scanf("%d", &T);
	for(i=0; i<T; i++){
		scanf("%d %d", &N, &M);
		listaAdj = malloc((N+1)*sizeof(Set));
		for(j=0; j<N+1; j++)
			makeSet(&listaAdj[j]);
		
		for(j=0; j<M; j++){
			scanf("%d %d", &u, &v);
			insert(v, &listaAdj[u]);
		}		
		loop = 0;		
		verificaCiclo(listaAdj, N+1, &loop);
		if(loop)
			printf("SIM\n");
		else
			printf("NAO\n");
		for(j=0; j<N+1; j++)
			freeSet(&listaAdj[j]); // Libera memória alocada para o set de cada aresta
	}
	return 1;			
}
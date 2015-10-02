#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Cada célula da lista contem o anagrama propriamente dito bem como os apontadores 
typedef struct anagrama{
	char anagrama[51];
	int count;
	struct anagrama *prev;
	struct anagrama *next;
} Anagrama;

// Lista de palavras
typedef struct {
	Anagrama *end; // Sentinela da lista
	int size;
} Set;

typedef Anagrama* iterator;

// Cria um conjunto vazio - O(1)
void makeSet(Set *s);

// Verifica se o conjunto está vazio - O(1)
int empty(Set *s);

// Retorna o número de elementos presente na lista - O(1)
int size(Set *s);

// Retorna o primeiro elemento da lista em O(1).
// Caso a lista esteja vaiza, retorna um ponteiro para end (sentinela da lista)
iterator begin(Set *s);

// Retorna o último elemento (sentinela) da lista
iterator end(Set *s);

// Retorna o elemento seguinte, apontado pelo iterador x - O(1)
iterator next(iterator x);

// Retorna o elemento anterior, apontado pelo iterador x - O(1)
iterator prev(iterator x);

// Retorna a chave (palavra) do elemento indicado por x - O(1)
char* key(iterator x);

// Retorna um iterador para o elemento k em O(n) ou para end se a busca não tiver sucesso
iterator find(char *k, Set *s);

// Insere k no conjunto em O(1) -set não ordenado-
void insert(char *k, Set *s);

// Remove k do conjunto (caso exista) em O(n)
void erase(char *k, Set *s);

// Remove todos os elementos do conjunto em O(n)
void clear(Set *s);

// Libera toda a memória alocada para o conjunto em O(n)
void freeSet(Set *s);
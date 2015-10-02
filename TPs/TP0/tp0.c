#include "linkedlist.h"

int cmpChar(const void* a, const void* b){
	return strcmp(a, b);
}

int cmpInt(const void* a, const void* b){
	return (*(int*)b - *(int*)a);
}

char* sortWord(char* word){
	qsort(word, strlen(word), sizeof(char), cmpChar);
	return word;
}

int main(){
	// Cria a lista de anagramas
	Set anagramas;
	makeSet(&anagramas);
	int n; // Número de listas a serem processadas
	int i; // Iterador das listas existentes na entrada
	int c; // Iterador do arranjo de contadores
	int *contadores; // Arranjo que armazenará os contadores de cada anagrama
	char aux[51]; // String auxiliar de leitura das palavras
	char separator; // Separador entre as palavras das listas
	iterator j, a; // Iterador de anagramas para percorrer a lista encadeada
	scanf("%d", &n); // Le a quantidade de listas de palavras a serem processadas
	for(i=0; i<n; i++){ // O(n)
		separator = ' ';
		// Enquanto não chegar ao final da linha, a lista é lida
		while(separator != '\n'){ // O(p)
			scanf("%s%c", aux, &separator);
			// Insere o anagrama. Se já existir na lista, ele não será adicionado
			insert(sortWord(aux), &anagramas); // O(p) + O(c log c)
		}
		// Aloca um vetor de inteiros para armazenar os contadores
		contadores = malloc(size(&anagramas)*sizeof(int));
		a = begin(&anagramas); // Obtém o início do Set
		c = 0; // Zera o contador para iniciar o preenchimento do novo arranjo 
		for(j=a; j != end(&anagramas); j=next(j)){ // O(p)
			contadores[c] = j->count;
			c++;
		}
		// Ordena a saída pela quantidade de palavras por grupo de anagrama
		qsort(contadores, size(&anagramas), sizeof(int), cmpInt); // O(p log p)
		for(c=0; c<size(&anagramas); c++){ // O(p)
			if(c < size(&anagramas)-1)
				printf("%d ", contadores[c]);
			else
				printf("%d", contadores[c]);
		} 
		printf("\n");
		//freeSet(&anagramas); // libera a memóra utilizada pela lista
		clear(&anagramas); // O(p)
		free(contadores); // libera a memórica alocada para o arranjo
	}
	freeSet(&anagramas);
	return 0;
}
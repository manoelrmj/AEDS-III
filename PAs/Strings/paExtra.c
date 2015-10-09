#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estruturas e métodos para a lista encadeada

typedef struct word{
	char word[30];
	int count;
	struct word *prev;
	struct word *next;
} Word;

typedef Word* iterator;

typedef struct {
	Word *end;
	int size;
} Set;

void makeSet(Set *s){
	s->size = 0;
	s->end = malloc(sizeof(Word));
	s->end->next = s->end;
	s->end->prev = s->end;
}

iterator begin(Set *s){
	return s->end->next;
}

iterator end(Set *s){
	return s->end;	
}

char* key(iterator x){
	return x->word;
}

iterator prev(iterator x){
	return x->prev;
}

iterator next(iterator x){
	return x->next;
}

iterator find(char *k, Set *s){
	iterator i;
	for(i = begin(s); i != end(s); i = next(i)){
		if(strcmp(key(i), k) == 0)
			return i;		
	}
	return end(s); // Busca sem sucesso
}

int empty(Set *s){
	return s->size == 0;
}

void insert(char *k, Set *s){
	iterator w = find(k, s);
	if(w == end(s)){ // Se a palavra não existir na lista, adicioná-la
		Word *w = malloc(sizeof(Word));
		strcpy(w->word, k);
		w->count = 1;		
		w->prev = end(s)->prev;
		w->prev->next = w;
		w->next = end(s);
		end(s)->prev = w;
		s->size++;
	}else{
		w->count++;
	}
}

void erase(char *k, Set *s){
	Word *w = find(k, s);
	if(w != end(s)){
		w->prev->next = w->next;
		w->next->prev = w->prev;
		free(w);
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

int main(){
	char aux[31];
	char sentence[10001];
	char separator;
	int i, count, stop;	
	Set words[26];	
	int maxCh;
	iterator it;
	char auxWord[31];
	Set shortened[26];
	strcpy(aux, ""); 
	// Inicializa os sets de palavras e abreviações
	for(i=0; i<26; i++){
		makeSet(&words[i]);
		makeSet(&shortened[i]);
	}		
	while(strcmp(aux, ".") != 0){
		separator = ' ';
		// Inicializa a string de sentença com uma string vazia
		strcpy(sentence, "");
		while(separator != '\n'){
			scanf("%s%c", aux, &separator);
			if(strcmp(aux, ".") == 0)
				break;
			strcat(sentence, aux); // Adiciona a palavra lida à frase
			strncat(sentence, &separator, 1); // Adiciona o caracter separador
			if(strlen(aux) > 2)
				insert(aux, &words[aux[0]-97]);				
		}
		
		// Busca pelas palavras a serem abreviadas		
		count = 0;
		for(i=0; i<26; i++){
			maxCh = 0;
			if(!empty(&words[i])){
				count++;
				for(it=begin(&words[i]); it != end(&words[i]); it=next(it)){
					if((strlen(it->word)-2)*it->count > maxCh){
						maxCh = (strlen(it->word)-2)*it->count;
						strcpy(auxWord, it->word);
					}
				}
				insert(auxWord, &shortened[i]);				
			}
		}
		if(strcmp(aux, ".") != 0){ // Não exibe saída para a última linha
			i=0;
			stop = 0;
			strcpy(aux, "");
			while(!stop){
				if(sentence[i] != ' ' && sentence[i] != '\n'){
					strncat(aux, &sentence[i], 1);	
				}else{
					// Verifica se a palavra lida foi abreviada
					if(find(aux, &shortened[aux[0]-97]) != end(&shortened[aux[0]-97]))
						printf("%c.", aux[0]);
					else
						printf("%s", aux);
					strcpy(aux, "");
					if(sentence[i] == '\n')
						stop = 1;
					else
						printf(" ");
				}
				i++;
			}			
			printf("\n");
			printf("%d\n", count);
			for(i=0; i<26; i++)
				if(!empty(&shortened[i]))	
					printf("%c. = %s\n", begin(&shortened[i])->word[0], begin(&shortened[i])->word);
		}

		for(i=0; i<26; i++){
			clear(&words[i]);		
			clear(&shortened[i]);
		}		
	}
}
#include "linkedlist.h"

void makeSet(Set *s){
	s->size = 0;
	s->end = malloc(sizeof(Anagrama));
	s->end->next = s->end;
	s->end->prev = s->end;
}

int empty(Set *s){
	return s->size == 0;
}

int size(Set *s){
	return s->size;
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

char* key(iterator x){
	return x->anagrama;
}

iterator find(char *k, Set *s){
	iterator i;
	for(i = begin(s); i != end(s); i = next(i)){
		if(strcmp(key(i), k) == 0)
			return i;		
	}
	return end(s); // Busca sem sucesso
}

void insert(char *k, Set *s){
	iterator a = find(k, s);
	if(a == end(s)){ // Se o anagrama não existir na lista, inseri-lo
		Anagrama *a = malloc(sizeof(Anagrama));
		strcpy(a->anagrama, k);
		a->count = 1; // A primeira palavra inserida define um anagrama
		a->prev = end(s)->prev;
		a->prev->next = a;
		a->next = end(s);
		end(s)->prev = a;
		s->size++;
	}else{
		a->count++;
	}
}

void erase(char *k, Set *s){
	Anagrama *a = find(k, s);
	if(a != end(s)){ // Se o anagrama exisitr
		a->prev->next = a->next;
		a->next->prev = a->prev;
		free(a);
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
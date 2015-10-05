#include "linkedlist.h"

void makeSet(Set *s){
	s->size = 0;
	s->end = malloc(sizeof(Street));
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

int key(iterator x){
	return x->destination;
}

iterator find(int k, Set *s){
	iterator i;
	for(i = begin(s); i != end(s); i = next(i)){
		if(key(i) == k)
			return i;		
	}
	return end(s); // Busca sem sucesso
}

void insert(int destination, float probability, Set *s){ // Insere uma rua na lista de adjacência
	iterator i = find(destination, s);
	if(i == end(s)){ // Se a rua não existir na lista, inseri-la (TODO: Check if this is necessary)
		Street *st = malloc(sizeof(Street));
		st->destination = destination;
		st->probability = probability;
		st->prev = end(s)->prev;
		st->prev->next = st;
		st->next = end(s);
		end(s)->prev = st;
		s->size++;
	}
}

void erase(int k, Set *s){
	Street *st = find(k, s);
	if(st != end(s)){ // Se a rua exisitr
		st->prev->next = st->next;
		st->next->prev = st->prev;
		free(st);
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
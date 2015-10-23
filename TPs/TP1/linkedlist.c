#include "linkedlist.h"

void makeSet(Set *s){
	s->size = 0;
	s->end = malloc(sizeof(Street));
	s->end->next = s->end;
	s->end->prev = s->end;
}

int emptySet(Set *s){
	return s->size == 0;
}

int setSize(Set *s){
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

// Insere uma rua na lista de adjacência (ordenadamente)
void insert(int destination, double probability, Set *s){ 
	iterator i = begin(s);
	while(i != end(s) && key(i) < destination){
		i = next(i);
	}
	if(i == end(s) || key(i) != destination){
		Street *st = malloc(sizeof(Street));
		st->destination = destination;
		st->probability = probability;
		st->prev = i->prev;
		st->next = i;
		i->prev->next = st;
		i->prev = st;
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
	while(!emptySet(s))
		erase(key(begin(s)), s);
}

void freeSet(Set *s){
	clear(s);
	free(s->end);
}

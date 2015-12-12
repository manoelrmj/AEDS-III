#include <stdlib.h>
#include "stack.h"

void make_stack(stack* s, int capacity) {
  s->array = malloc(capacity*sizeof(SType));
  s->size = 0;
}

int empty(stack* s) {
  return s->size == 0;
}

int size(stack* s) {
  return s->size;
}

SType top(stack* s) {
  return s->array[s->size - 1];
}

void push(SType k, stack* s) {
  s->array[s->size] = k;
  s->size++;
}

void pop(stack* s) {
  s->size--;
}

void copy(stack* s, stack* p) {
  int i;
  s->size = p->size;
  for (i = 0; i < p->size; i++) {
    s->array[i] = p->array[i];
  }
}

void free_stack(stack* s) {
}

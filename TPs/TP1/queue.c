#include "queue.h"
#include <stdlib.h>

void makeQueue(queue* q) {
  q->size = 0;
  q->end = malloc(sizeof(Node));
  q->end->next = q->end;
  q->end->prev = q->end;
}

int emptyQueue(queue* q) {
  return q->size == 0;
}

int queueSize(queue* q) {
  return q->size;
}

Node* front(queue* q) {
  return q->end->next;
}

Node* back(queue* q) {
  return q->end->prev;
}

void push(int k, int dist, queue* q) {
  // Cria um novo nó e define o valor dos seus campos.
  Node* node = malloc(sizeof(Node));
  node->key = k;
  node->distance = dist;
  node->prev = q->end->prev;
  node->next = q->end;
  // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
  q->end->prev->next = node;
  q->end->prev = node;
  q->size++;
}

void pop(queue* q) {
  Node* first = q->end->next;  // Ponteiro para o primeiro elemento na fila.
  first->prev->next = first->next;
  first->next->prev = first->prev;
  free(first);
  q->size--;
}

void freeQueue(queue* q) {
  // Primeiramente, remove todos os elementos da fila.
  while (!emptyQueue(q)) {
    pop(q);  // A função pop() libera a memórima de cada nó removido da fila;
  }
  // Em seguida, libera a memória alocada ao sentinela.
  free(q->end);
}

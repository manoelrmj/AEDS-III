#ifndef QUEUE_H_
#define QUEUE_H_

// Tipo de dado da fila. Cada nó representa um quarteirão
typedef struct node{
  int key;
  int distance;
  struct node* prev;
  struct node* next;
} Node;

// Define um tipo de dado queue (Fila).
typedef struct {
  Node* end;  // Ponteiro para o sentinela.
  int size;  // Número de elementos na fila.
} queue;

// Cria uma fila vazia em O(1).
void makeQueue(queue* q);

// Testa se a fila está vazia em O(1).
int emptyQueue(queue* q);

// Retorna o número de elementos na fila em O(1).
int queueSize(queue* q);

// Retorna o elemento que está no início da fila em O(1).
// Precondição: a fila não pode estar vazia.
Node* front(queue* q);

// Retorna o elemento que está no final da fila em O(1).
// Precondição: a fila não pode estar vazia.
Node* back(queue* q);

// Insere k no final da fila em O(1).
void push(int k, int dist, queue* q);

// Remove o elemento que está no início da fila em O(1).
// Precondição: a fila não pode estar vazia.
void pop(queue* q);

// Libera a memória alocada para todos os elementos da fila em O(n),
// onde n é o número de elementos na fila.
void freeQueue(queue* q);

#endif  // QUEUE_H_

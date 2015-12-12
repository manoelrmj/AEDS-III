#ifndef STACK_H_
#define STACK_H_

// Tipo dos elementos na pilha.
typedef int SType;

// Define um tipo de dado stack (Pilha).
// Nesta implementação, o número máximo de elementos é igual a 1000.
typedef struct {
  SType *array;  // Vetor que contém os elementos da pilha.
  int size;  // Número de elementos na pilha.
} stack;

// Cria uma pilha vazia em O(1).
void make_stack(stack* s, int capacity);

// Testa se a pilha está vazia em O(1).
int empty(stack* s);

// Retorna o número de elementos na pilha em O(1).
int size(stack* s);

// Retorna o elemento que está no topo da pilha em O(1).
// Precondição: a pilha não pode estar vazia.
SType top(stack* s);

// Insere k no topo da pilha em O(1).
void push(SType k, stack* s);

// Remove o elemento que está no topo da pilha em O(1).
// Precondição: a pilha não pode estar vazia.
void pop(stack* s);

// Faz a pilha s ficar igual a p em O(n + m),
// onde n = size(s) e m = size(p).
void copy(stack* s, stack* p);

// Libera a memória alocada para a pilha em O(n), onde n = size_.
void free_stack(stack* s);

#endif  // STACK_H_

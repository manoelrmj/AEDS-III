#include <stdio.h>

// Registro do carro no estacionamento
typedef struct {
	int hC; // Horário chegada
	int hS; // Horário saída
} Carro;

// Tipo dos elementos na pilha.
typedef Carro SType;

/*	Define um tipo de dado stack (Pilha).
*	Nesta implementação, o número máximo de elementos é igual a 1000,
*	que equivale à capacidade do estacionamento.
*/
typedef struct {
  Carro array[10001];  // Vetor que contém os elementos da pilha.
  int size;  // Número de elementos na pilha.
} stack;

void make_stack(stack* s) {
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

int main(){
	int N = -1; // # motoristas
	int K = -1; // # carros
	int C, S; // Horário de chegada/saída
	int i, j, stop;
	Carro c;
	stack st;
	make_stack(&st);
	scanf("%d %d", &N, &K);	
	while(N != 0 && K != 0){
		stop = 0;
		for(i=0; i<N; i++){
			scanf("%d %d", &C, &S);
			c.hC = C;
			c.hS = S;
			if(empty(&st) || c.hC < top(&st).hS){
				if(size(&st)+1 > K){
					stop = 1;
				}else{
					push(c, &st);				
				}
			}else if(c.hC >= top(&st).hS){
				while(c.hC >= top(&st).hS){
					pop(&st);									
				}
				for(j=0; j<size(&st); j++){
					if(c.hS > st.array[j].hS){
						stop = 1;
					}
				}
				if(size(&st)+1 > K){
					stop = 1;
				}else{
					push(c, &st);
				}
			}
		}
		if(stop)
			printf("Nao\n");
		else
			printf("Sim\n");		
		scanf("%d %d", &N, &K);		
	}
	return 0;
}
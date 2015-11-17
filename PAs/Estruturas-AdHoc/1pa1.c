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
	int N, K , C, S;
	int i, j, stop;
	scanf("%d %d", &N, &K);
	while(N!=0 && K!=0){		
		Carro c;
		stack st;
		make_stack(&st);
		stop = 0;
		for(i=0; i<N; i++){
			scanf("%d %d", &C, &S);
			c.hC = C;
			c.hS = S;
			if(empty(&st)){ // Se a fila estiver vazia, inserir o carro
				push(c, &st);
			}else{ // caso contrário, verificar se haverá remoção
				while(c.hC >= top(&st).hS && !empty(&st)){
					pop(&st);
				}
				// Verifica se a pilha irá estourar
				if(size(&st)+1 > K){
					stop = 1;
				}else{
					push(c, &st);
				}
				// Verifica se um carro trava outro
				for(j=size(&st)-1; j>0; j--){
					if(st.array[j].hS > st.array[j-1].hS){
						stop = 1;
					}
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
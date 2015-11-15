#include "guloso.h"

int getDistancia(int* planetasAVisitar, int n, int* distancia);
void fooR(int* src, int* v, int srcIndex, int vIndex, int srcSize, int vSize, int *dist, int* maiorDistancia);
void foo(int* src, int size, int k, int *dist, int* maiorDistancia);
void bruteForce(int numPlanetas, int numConquista, int *distancia);
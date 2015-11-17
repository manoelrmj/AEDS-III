#include "guloso.h"

int getDistancia(int* planetasAVisitar, int n, int* distancia);
void comb(int* src, int* v, int srcIndex, int vIndex, int srcSize, int vSize, int *dist, int* maiorDistancia);
void bruteForce(int numPlanetas, int numConquista, int *distancia);
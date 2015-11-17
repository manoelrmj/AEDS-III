#include "guloso.h"

int* copiaVetor(int* array, int n){
    int i;
    int *novoArray = calloc(n, sizeof(int));
    for(i=0; i<n; i++)
        novoArray[i] = array[i];   
    return novoArray;
}

void greedy(int numPlanetas, int numConquista, int *distancia){
    int i, j;
    int* distanciaAux = copiaVetor(distancia, numPlanetas+1);
    int numArestas = numPlanetas+1;
    int naoConquistados = numPlanetas - numConquista;
    int tmpPlaneta, tmpDistancia;
    // Encontra a possível menor aresta eliminando algum planeta
    for(i=0; i<naoConquistados; i++){
        tmpDistancia = INT_MAX;
        for(j=0; j<numArestas-1; j++){
            if(distanciaAux[j]+distanciaAux[j+1] < tmpDistancia){
                tmpDistancia = distanciaAux[j]+distanciaAux[j+1];
                tmpPlaneta = j;
            }
        }
        printf("(dist: %d, plt: %d)\n", tmpDistancia, tmpPlaneta);
        distanciaAux[tmpPlaneta] = tmpDistancia;
        for(j=tmpPlaneta+1; j<numArestas; j++){
            distanciaAux[j] = distanciaAux[j+1];
        }
        numArestas--;
        for(j=0; j<numArestas; j++){
            printf("%d ", distanciaAux[j]);
        }
        printf("\n");
    }
    tmpDistancia = 0;
    for(j=0; j<numArestas; j++){
        if(distanciaAux[j] > tmpDistancia)
            tmpDistancia = distanciaAux[j];
    }
    printf("%d\n", tmpDistancia);
}
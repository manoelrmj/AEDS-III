#include "forcaBruta.h"

/*	Este método retorna a maior distância percorrida pela dado um conjunto de 
	planetas a serem visitados */
int getDistancia(int* planetasAVisitar, int n, int* distancia){
	int distSize = n+1;
	int* distanciaAux = copiaVetor(distancia, distSize);
	int i, j;
	for(i=0; i<n; i++){
		if(!planetasAVisitar[i]){
			j = i;
			while(!planetasAVisitar[i] && i<n){
				distanciaAux[j] += distanciaAux[i+1];
				i++;
			}
		}
	}
	/* Encontra a maior distância percorrida depois de unidas as arestas
		relativas aos planetas que não serão visitados */
	int maiorDistancia = 0;
	for(i=0; i<distSize; i++){
		if(distanciaAux[i] > maiorDistancia)
			maiorDistancia = distanciaAux[i];
	}
	/*printf("%d\n", maiorDistancia);
	printf("Planetas a visitar: \n");
	for(i=0; i<n; i++){
		printf("%d ", planetasAVisitar[i]);
	}
	printf("\n");
	printf("Distancias (size = %d): \n", distSize);
	for(i=0; i<distSize; i++){
		printf("%d ", distanciaAux[i]);
	}
	printf("\n\n");*/
	free(distanciaAux);
	return maiorDistancia;
}

void comb(int* src, int* v, int srcIndex, int vIndex, int srcSize, int vSize, int* dist, int* maiorDistancia){
	int i;
	if(vIndex==vSize){
		int* planetasAVisitar = calloc(srcSize+1, sizeof(int));
		int auxDist;
		for(i=0; i<vSize; i++){
			//printf("%d ", v[i]);
			planetasAVisitar[v[i]-1] = 1;			
		}
		auxDist = getDistancia(planetasAVisitar, srcSize, dist);
		if(auxDist < *maiorDistancia)
			*maiorDistancia = auxDist;
		free(planetasAVisitar);
		/*printf("\nVisit? : ");
		for(i=0; i<srcSize; i++){
			printf("%d ", planetasAVisitar[i]);
		}
		printf("\n");*/
	}
	else{
		for(i=srcIndex; i<srcSize; i++){
			v[vIndex] = src[i];
			comb(src, v, i+1, vIndex+1, srcSize, vSize, dist, maiorDistancia);
		}
	}
}

void bruteForce(int numPlanetas, int numConquista, int *distancia){
	int i;
	// Variável que armazenará a menor distância máxima
	int maiorDistancia = INT_MAX;
	// Vetor que indica se o planeta será visitado ou não
	int* p = (int*)malloc(numPlanetas*sizeof(int));
	// Vetor utilizado na combinação
	int* v = (int*)calloc(numConquista, sizeof(int));

	for(i=0; i<numPlanetas; i++)
		p[i] = i+1;	
	comb(p, v, 0, 0, numPlanetas, numConquista, distancia, &maiorDistancia);
	printf("%d\n", maiorDistancia);
	free(p);
	free(v);

}


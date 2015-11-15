#include "guloso.h"
#include "forcaBruta.h"

static const char *optString = "a:h";

int main(int argc, char **argv){
	int opt = 0;
	char *strategy;
    opt = getopt(argc, argv, optString);

    int T; // Número de instâncias do problema
    int N; // Número de planetas na rota
    int K; // Número de planetas a serem reconquistados
    int i, j; // Variáveis auxiliares
    int *dist; // Vetor de distância entre planetas

    // Leitura do parâmetro de execução (paradigma)
    while(opt != -1) {
        switch( opt ) {
            case 'a':
                strategy = optarg;
                break;
            
            case 'h':
                puts("Execute com o parametro -a estrategia_de_solucao [PD | AG | FB]");
                exit(EXIT_FAILURE);
                break;
                
            default:
                /* It won't actually get here. */
                break;
        }
        
        opt = getopt(argc, argv, optString);
    }

    scanf("%d", &T);
    for(i=0; i<T; i++){
    	scanf("%d %d", &N, &K);
    	dist = calloc(N+1, sizeof(int));
    	for(j=0; j<N+1; j++)
    		scanf("%d", &dist[j]);

    	/*for(j=0; j<N+1; j++)
    		printf("%d", dist[j]);
    	printf("\n");*/
    	
        if(!strcmp(strategy, "PD")){
            // Programação dinâmica
        }else if(!strcmp(strategy, "AG")){
            // Algorítmo guloso
            greedy(N, K, dist);
        }else if(!strcmp(strategy, "FB")){
            // Força bruta
            bruteForce(N, K, dist);
        }else{
            printf("Algoritmo invalido\n");
            exit(EXIT_FAILURE);
        }
    	free(dist);    	
    }

    return 0;
}
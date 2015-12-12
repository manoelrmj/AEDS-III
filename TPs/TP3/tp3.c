#include "comb.h"
#include <unistd.h>
#include <math.h>

static const char *optString = "t:h";

int main(int argc, char **argv){
    int opt = 0;
	int qtdThreads = 0;
	int qtdInstancias = 0;
    int i, j, soma;
    int qtdeAlimentos = 0;
    int calorias[300];
    int auxCaloria = 0;
    char separator;
	opt = getopt(argc, argv, optString);
	// Leitura do parâmetro de execução (número de threads)
    while(opt != -1) {
        switch( opt ) {
            case 't':
                qtdThreads = atoi(optarg);
                break;
            
            case 'h':
                puts("Execute com o parametro -t <quantidade_de_threads>");
                exit(EXIT_FAILURE);
                break;
                
            default:
                break;
        }
        
        opt = getopt(argc, argv, optString);
    }
    scanf("%d", &qtdInstancias);
    for(i=0; i<qtdInstancias; i++){
        // Inicializa o arranjo de calorias
        for(j=0; j<300; j++)
            calorias[j] = 0;

        qtdeAlimentos=0;
        separator = ' ';
        scanf("%d", &soma);
        //printf("%d\n", soma);
        while(separator != '\n'){
            scanf("%d%c", &auxCaloria, &separator);
            calorias[qtdeAlimentos] = auxCaloria;
            qtdeAlimentos++;
        }
        printf("Entrada: %d alimentos\n", qtdeAlimentos);
        /*
        for(k=0; k<qtdeAlimentos; k++)
            printf("%d ", calorias[k]);
        printf("\n");*/

        /* COMB */
        verificaSolucao(calorias, qtdeAlimentos, soma, qtdThreads);
        //genComb(calorias, qtdeAlimentos, 2, soma);
        /* COMB */
    }
	return 0;
}
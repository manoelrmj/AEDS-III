#include <pthread.h>
#include "comb.h"

void comb(int* conjunto, int* v, int srcIndex, int vIndex, int qtdeAlimentos, int vSize, int consumo, int *flagEncontrado){
    int i, soma;
    if(vIndex==vSize){
        soma = 0;
        /*for(i=0; i<vSize; i++)
            printf("%d ", v[i]);*/
        //printf("\n");
        for(i=0; i<vSize; i++)
            soma += v[i];
        //printf(" Soma: %d\n", soma);
        if(soma == consumo){
            //printf("SIM\n");
            (*flagEncontrado) = 1;
        }
    }
    else{
        for(i=srcIndex; i<qtdeAlimentos; i++){
            v[vIndex] = conjunto[i];
            if(!(*flagEncontrado))
                comb(conjunto, v, i+1, vIndex+1, qtdeAlimentos, vSize, consumo, flagEncontrado);
        }
    }
}

void genComb(int* calorias, int qtdeAlimentos, int k, int consumo, int* flagEncontrado){
    int *escolhidos;
    escolhidos = (int*)calloc(k, sizeof(int));
    comb(calorias, escolhidos, 0, 0, qtdeAlimentos, k, consumo, flagEncontrado);
    free(escolhidos);
}

void* executaThread(void* arg){
    threadArg* t_arg = (threadArg*) arg;
    printf("Thread executou! %d - %d\n", t_arg->combInicial, t_arg->combFinal);
}

int verificaSolucao(int* calorias, int qtdeAlimentos, int soma, int qtdeThreads){
    int solucaoEncontrada = 0;
    int idComb = 1;
    int i, carga, status;
    // Define o número de combinações por thread
    if(qtdeThreads >= qtdeAlimentos){
        carga = 1;
        qtdeThreads = qtdeAlimentos;
    }
    else{
        carga = round((double)qtdeAlimentos/(double)qtdeThreads);
    }
    
    // Gera argumentos das threads
    threadArg *t_arg = (threadArg*) malloc(qtdeThreads*sizeof(threadArg));
    /* Inicializa as combinações, que, a princípio, são nulas.
     * Dependendo da distribuição das combinações entre as threads,
     * algumas threads podem ficar sem entradas para processar   
     */
    for(i=0; i<qtdeThreads; i++){
        t_arg[i].combInicial = 0;
        t_arg[i].combFinal = 0;
    }
    for(i=0; i<qtdeThreads; i++){
        t_arg[i].combInicial = idComb;
        if(idComb+(carga-1) < qtdeAlimentos)
            t_arg[i].combFinal = idComb+(carga-1);
        else
            t_arg[i].combFinal = qtdeAlimentos;        
        t_arg[i].calorias = calorias;
        t_arg[i].qtdeAlimentos = qtdeAlimentos;
        t_arg[i].soma = soma;
        t_arg[i].solucaoEncontrada = &solucaoEncontrada;
        if(t_arg[i].combFinal == qtdeAlimentos)
            break;
        else
            idComb+=carga;
    }
    /* Aloca as combinações que sobraram para a última thread,
    depois de ignorar as threads qur ficaram sem tarefas */
    i = qtdeThreads-1;
    while(t_arg[i].combInicial == 0 && t_arg[i].combFinal ==0)
        i--;
    t_arg[i].combFinal = qtdeAlimentos;
    
    /*for(i=0; i<qtdeThreads; i++){
        printf("Thread %d: %d - %d\n", i, t_arg[i].combInicial, t_arg[i].combFinal);
    }*/

    //exit(1);
    // Cria as threads
    pthread_t *threads = (pthread_t*) malloc(qtdeThreads*sizeof(pthread_t));
    for(i=0; i<qtdeThreads; i++){
        status = pthread_create(&threads[i], NULL, executaThread, &t_arg[i]);
        if(status){
            printf("Erro ao criar thread. pthread_create() retornou: %d\n", status);
            exit(-1);
        }
    }

    // join threads
    for(i=0; i<qtdeThreads; i++){
        pthread_join(threads[i], NULL); 
    }

    free(threads);
    free(t_arg);
    if(solucaoEncontrada)
        printf("sim\n");
    else
        printf("nao\n");
    
    return 0;
}
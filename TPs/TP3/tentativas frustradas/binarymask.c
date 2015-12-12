int* binaryMask(int n, int k){
    int *bits = (int*) malloc(k*sizeof(int));
    int i, bit;
    if(n==0){
        for(i=0; i<k; i++)
            bits[i] = 0;
        return bits;
    }                
    // Inicializa os valores da máscara
    for(i=0; i<k; i++)
        bits[i] = -1;
    while(n != 0){
        // Calcula o valor de cada bit
        bit = n%2;
        for(i=k-1; i>0; i--)
            bits[i] = bits[i-1];
        bits[0] = bit;
        n/=2;
    }
    // Desloca os valores para o final do vetor, até que o LSB fique na última posição
    int numDeslocamentos = 0;
    while(bits[k-1] == -1){
        for(i=k-1; i>0; i--){
            bits[i] = bits[i-1];    
        }
        numDeslocamentos++;
    }
    for(i=0; i<numDeslocamentos; i++)
        bits[i] = 0;
    return bits;    
}
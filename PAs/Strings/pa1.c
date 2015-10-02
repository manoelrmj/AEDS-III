#include <stdio.h>

void main(){
	int alfabeto[26];
	int N; // qtde de casos de teste
	int i, j; 
	char ch;
	int count;
	scanf("%d", &N);
	scanf("%c", &ch); // Lê a qubra de linha após a leitura de N
	for(i=0; i< N; i++){
		// Inicializa o arranjo para cada entrada
		for(j=0; j<26; j++)
			alfabeto[j] = 0;
		count = 0;
		ch = 0;		
		while(ch != 10){ // Enquanto não terminar a linha, ler os caracteres e preencher o arranjo
			scanf("%c", &ch);
			switch(ch){
				case 10: // 'new line'					
				case 32: // ' '
				case 44: // ','
				break;
				
				default:
					if(alfabeto[ch-97] != 1){
						alfabeto[ch-97] = 1;
						count++;
					}
				break;				
			}
		}
		if(count == 26)
			printf("frase completa\n");
		else if(count < 13)
			printf("frase mal elaborada\n");
		else
			printf("frase quase completa\n");
	}
}
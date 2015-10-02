#include <stdio.h>

void main(){
	int lists, words, size, i, j, k;
	char ch;
	printf("Qtde de listas:  ");
	scanf("%d", &lists);
	printf("Qtde de palavras:  ");
	scanf("%d", &words);
	printf("Tamanho das palavras:  ");
	scanf("%d", &size);

	FILE *arq;
	arq = fopen("saida.txt", "w");
	
	//Generate file
	fprintf(arq, "%d\n", lists);		
	srand(time(NULL));
	for(i=0; i<lists; i++){
		for(j=0; j<words; j++){
			for(k=0; k<size; k++){
				ch = 'a' + rand()%26;
				fprintf(arq, "%c", ch);
			}
			if(j != words-1)
				fprintf(arq, " ");
		}
		fprintf(arq, "\n");	
	}
	//fprintf(arq, "\n");	
	fclose(arq);	
}
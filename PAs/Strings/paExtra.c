#include <stdio.h>
#include <string.h>

typedef struct word{
	char word[30];
	int length;
} Word;

int main(){
	char separator;
	int i, count, end;
	char aux[30];
	Word abreviation[26]; // Vetor de abreviações 
	char sentence[10000];
	strcpy(aux, ""); // Inicializa a string auxiliar
	while(strcmp(aux, ".") != 0){
		separator = ' ';
		// Inicializa o arranjo de abreviações
		for(i=0; i<26; i++){
			strcpy(abreviation[i].word, "");
			abreviation[i].length = -1;
		}
		// Inicializa a string de sentença com uma string vazia
		strcpy(sentence, "");
		count = 0;	
		while(separator != '\n'){
			scanf("%s%c", aux, &separator);
			if(strcmp(aux, ".") == 0)
				break;
			strcat(sentence, aux); // Adiciona a palavra lida à frase
			strncat(sentence, &separator, 1); // Adiciona o caracter separador
			
			/* Verifica se já existe uma possível abreviação para a palavra em 
			 * questão. Caso não exista, inserir esta palavra. Se já existir, 
			 * verificar se utilizar a nova palavra como abreviação permite que 
			 * se obtenha um post menor.
			 */
			if(abreviation[aux[0]-97].length == -1 && strlen(aux) > 2){
				strcpy(abreviation[aux[0]-97].word, aux);
				abreviation[aux[0]-97].length = strlen(aux);
				count++;								
			}else{
				if(strlen(aux) > abreviation[aux[0]-97].length && strlen(aux) > 2){
					strcpy(abreviation[aux[0]-97].word, aux);
					abreviation[aux[0]-97].length = strlen(aux);
				}
			}
		}
		
		if(strcmp(aux, ".") != 0){ // Não exibe saída para a última linha
			i=0;
			end = 0;
			strcpy(aux, "");
			while(!end){
				if(sentence[i] != ' ' && sentence[i] != '\n'){
					strncat(aux, &sentence[i], 1);	
				}else{
					// Verifica se a palavra lida foi abreviada
					if(!strcmp(aux, abreviation[aux[0]-97].word))
						printf("%c.", aux[0]);
					else
						printf("%s", aux);
					strcpy(aux, "");
					if(sentence[i] == '\n')
						end = 1;
					else
						printf(" ");
				}
				i++;
			}			
			printf("\n");
			printf("%d\n", count);
			for(i=0; i<26; i++){
				if(abreviation[i].length != -1){
					printf("%c. = %s\n", abreviation[i].word[0], abreviation[i].word);
				}
			}	
		}		
	}
	return 0;
}
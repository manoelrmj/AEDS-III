#include <stdio.h>
#include <ctype.h>
#include <math.h>

// Desloca 3 caracteres p/ direita
void cypher1(char *line){ 
	int j=0;
	while(line[j] != 10){
		if(isalpha(line[j]))
			line[j] = line[j]+3;		
		j++;
	}	
}

// Inverte a string
void cypher2(char *line){ 
	int i, j, n=0;
	char aux;
	while(line[n] != 10) 
		n++;	
	j = n-1;
	for(i=0; i<floor(n/2); i++){
		aux = line[i];
		line[i] = line[j];
		line[j] = aux;
		j--;
	}
}

// Desloca caracteres da metade em diante p/ esquerda
void cypher3(char *line){ 
	int i, n=0;
	while(line[n] != 10) 
		n++;
	for(i=floor(n/2); i<n; i++)
		line[i] = line[i]-1;		
}

void main(){
	int i, n, j;	
	char ch;
	char line[1000];
	scanf("%d", &n); 
	scanf("%c", &ch);
	for(i=0; i<n; i++){
		ch = 0;
		j=0;
		while(ch != 10){
			scanf("%c", &ch);
			line[j] = ch;
			j++;
		}		
		cypher1(line);		
		cypher2(line);		
		cypher3(line);
		j=0;
		while(line[j] != 10){
			printf("%c", line[j]);
			j++;			
		}
		printf("\n");
	}		
}
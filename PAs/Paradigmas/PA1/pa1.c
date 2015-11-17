#include <stdio.h>
#include <stdlib.h>

void main(){
	int n, i;
	int *a;
	char aux;
	long long trabalho = 0;
	scanf("%d", &n);
	while(n != 0){
		a = malloc(n*sizeof(int));
		for(i=0; i<n; i++)
			scanf("%d%c", &a[i], &aux);							
		for(i=1; i<n; i++){
			a[i] += a[i-1];
			a[i-1] < 0 ? (trabalho += (-1) * a[i-1]) : (trabalho += a[i-1]);
		}
		printf("%lld\n", trabalho);
		free(a);
		trabalho = 0;
		scanf("%d", &n);
	}
}

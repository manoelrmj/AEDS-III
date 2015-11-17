#include <stdio.h>
#include <stdlib.h>

int fib(int n, int *count){
	int i, result;
	int *fib_calc = calloc((n+1), sizeof(int));
	int *fib_call = calloc((n+1), sizeof(int));
	fib_calc[0] = 0;
	fib_calc[1] = 1;
	(*count) = 0;
	if(n <= 1)
		return n;
	for(i=2; i<=n; i++){
		fib_calc[i] = fib_calc[i-1] + fib_calc[i-2];
		fib_call[i] = fib_call[i-1] + fib_call[i-2] + 2;
	}
	(*count) = fib_call[n];
	result = fib_calc[n];
	free(fib_calc);
	free(fib_call);
	return result;
}

int main(){
	int i, n, x, count;
	scanf("%d", &n);
	for(i=0; i<n; i++){
		scanf("%d", &x);
		printf("fib(%d) = %d calls = %d\n", x, count, fib(x, &count));	
	}
	return 0;
}
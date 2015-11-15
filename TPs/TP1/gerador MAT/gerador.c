#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main() {
  int n = 10;
  int mat[1000][1000];
  int i, j;
  int v, e, source, target, range, d;
  int rand_factor;
  scanf("%d %d %d %d %d", &v, &e, &range, &d, &rand_factor);
  srand(time(NULL) + rand_factor);
  int casos = 50;
  printf("%d\n", casos);
  int cont;
  for (cont = 0; cont < casos; ++cont) {
    for (i = 0 ; i < v; ++i) {
      for (j = 0; j < v; ++j)
	mat[i][j] = 0;
      mat[i][i] = 1;
    }
    source = rand()%v;
    do {
      target = rand()%v;
    } while (target == source);
    printf("%d %d %d %d %d %d\n", v, e, source, target, range, d);
    for (i = 0; i < e; ++i) {
      int s = rand()%v;
      int t = rand()%v;
      if (mat[s][t]) --i;
      else printf("%d %d %.2lf\n", s, t, 0.2 + (rand()%21)/100.0);
      mat[s][t] = mat[t][s] = 1;
    }
    int proc[1000];
    for (i = 0; i < v; ++i) proc[i] = 0;
    for (i = 0; i < d; ++i) {
      int t = rand()%v;
      while (proc[t])
	t = rand()%v;
      printf("%d\n", t);
      proc[t] = 1;
    }
  }
  return 0;
}
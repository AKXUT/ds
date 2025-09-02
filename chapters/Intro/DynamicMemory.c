/*************************************************
 * Created by David on Tue Sep  2 15:37:34 2025  *
 *************************************************/
#include <stdio.h>
#include <stdlib.h>

void createArray(int **p, int n) {
  
  *p = malloc(n *sizeof(int));
}

int main()
{ int n = 1000;
  int *a;
  createArray(&a, n);
  return 0;
}

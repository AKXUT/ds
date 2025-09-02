/*************************************************
 * Created by David on Tue Sep  2 15:37:34 2025  *
 *************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>

void createArray(int **p, int n) {
  
  *p = malloc(n *sizeof(int));
}

int main()
{ int n = 600;
  int *a;
  size_t num_of_bytes;
  
  createArray(&a, n);
  num_of_bytes = malloc_size(a);
  printf("%d\n", num_of_bytes/sizeof(int));
  return 0;
}

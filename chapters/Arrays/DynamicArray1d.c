
// 动态内存分配
// malloc: memory allocation
#include<stdio.h>
#include<stdlib.h>
int * makearry(int sz);
void makearray2(int **p, int n);
int main() {
  int n, *arr, i;
  
  scanf("%d", &n);

  // arr = makearry(n);

  makearray2(&arr, n);
  
  for (i = 0; i < n; i++)
    arr[i] = i + 1;

  for (i = 0; i < n; i++)
    printf("%d ", arr[i]);
}


int * makearry(int sz) { return malloc(sizeof(int) * sz); }

void makearray2(int **p, int n) {
  (*p) = malloc(sizeof(int) * n);
}


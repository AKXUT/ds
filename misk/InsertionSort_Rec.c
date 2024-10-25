/******************************************************
 * Author:       David  Song                            *
 * Mail:         songxin@xaut.edu.cn                    *
 * Create Date: Fri Oct 25 18:07:44 2024                *
 * Last Modify:                                         *
 * Comment: a recurrisive insertion sort implementation *
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N 15

int cmp(const void *p, const void *q) {
  return *(int *)p - *(int *)q;
}

void PrintArr(int a[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");
}

void InsertionSortRec(int a[], int n) {
  int tmp, i;
  
  if (n == 1) return;
  
  InsertionSortRec(a, n-1);

  tmp = a[n-1];
  i = n - 2;
  while (i > -1 && a[i] > tmp) {
    a[i+1] = a[i];
    i--;
  }
  a[i+1] = tmp;
}


int main()
{
  int a[N], b[N];
  
  for (int i = 0; i < N; i++) {
    a[i] = rand() % 1000;
    b[i] = a[i];
  }

  qsort(a, N, sizeof(int), cmp);
  InsertionSortRec(b, N);
  
  PrintArr(a, N);
  PrintArr(b, N);
  return 0;
}


/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Fri Oct 25 17:39:34 2024                *
 * Last Modify:                                        *
 * Comment: a recursive binary search implementation  *
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N 15

int cmp(const void *p, const void *q) {
  return *(int *)p - *(int *)q;
}

int  BiSearch(int a[], int low, int high, int x) {
  int mid;
  if (low > high)          return -1;
  mid = (low + high) / 2;
  if (a[mid] == x)         return mid;
  else if (a[mid] > x)     return BiSearch(a, low, mid-1, x);
  else                     return BiSearch(a, mid+1, high, x);
}

void PrintArr(int a[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");
}

int main()
{
  int a[N];
  
  for (int i = 0; i < N; i++)
    a[i] = rand() % 1000;
  qsort(a, N, sizeof(int), cmp);

  for (int i = 0; i < N; i++) {
   int rst = BiSearch(a, 0, N-1, a[i]);
   printf("found %d in index %d\n", a[i], rst);
  }
    
    //PrintArr(a, N);
  return 0;
}

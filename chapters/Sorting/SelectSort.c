/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Sat Nov  2 21:13:10 2024               *
 * Last Modify:                                        *
 * Comment: 简单选择法排序的实现                         *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

void SelectSort(int a[], int n) {
  int i, j, min_idx, tmp;
  for (i = 0; i < n-1; i++) {
    min_idx = i;
    for (j = i + 1; j < n; j++) {
      if (a[j] < a[min_idx])
	min_idx = j;
    }
    if (min_idx != i) {
      tmp = a[i];
      a[i] = a[min_idx];
      a[min_idx] = tmp; 
    }
  }
}

int main()
{
  int a[10] = {10, 8, 1, 2, 9, 7, 4, 3, 6, 5};

  SelectSort(a, 10);

  for (int i = 0; i < 10; i++)
    printf("%d ", a[i]);
  return 0;
}

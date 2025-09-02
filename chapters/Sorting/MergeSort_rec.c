/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Thu Jun  9 10:02:57 2022                *
 * Last Modify:                                        *
 * Comment:  两路合并排序算法，递归版本                   *
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

int * swap;

void merge(int a[],int s,int m,int t){ //merge可在O(n)时间内完成
  int i = s, j = m+1, k = s;
  while (i <= m && j <= t)
    if (a[i] >= a[j]) swap[k++] = a[j++];
    else swap[k++]=a[i++];

  while(i <= m)   swap[k++] = a[i++];
  while(j <= t)   swap[k++] = a[j++];
  for(int i = s; i <=t; i++) a[i] = swap[i];
}
 
void MergeSort(int a[], int s, int t){
  if (s < t){//至少有2个元素
    int m = (s + t)/2; //取中点，中点分给子数组1
    MergeSort(a, s, m);
    MergeSort(a, m + 1, t);
    merge(a, s, m, t);
  }
}
 
int main(){
  int n, *a;
  scanf("%d", &n);
  a = malloc(sizeof(int) * n);
  swap = malloc(sizeof(int) * n);
  for(int i=0;i<n;i++)  scanf("%d", &a[i]);
  MergeSort(a, 0, n-1);
  for(int i=0;i<n;i++) printf("%d ", a[i]);
  return 0;	
}


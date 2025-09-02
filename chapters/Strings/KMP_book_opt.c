/*******************************************************************************
 * Author: David Song					                       *
 * Mail  : songxin@xaut.edu.cn                                                 * 
 * At    : XAUT  					                       *
 * Create Date: 2020-01-30                              *
 * Last Modify:                                                                *
 * Comment:                                                                    *
 ******************************************************************************/
#include <stdio.h> 
#include <string.h>

void Next(char *T, int next[], int n) {
  int j = 0, k = -1;
  next[0] = -1;
  //  while (j < n - 1) {
  while (j < n) {
    if (k==-1 || T[j] == T[k]) {
      j++;
      k++;
      if (T[j] != T[k])
	next[j] = k;
      else
	next[j] = next[k];
    }
    else
      k = next[k];
  }
}

int KMP(char *S, char *T, int m, int n) {// m是主串长度，n是子串长度
  int i = 0, j = 0, next[n];
  Next(T, next, n);
  //for (int w=0;w<n;w++) printf("%3d", next[w]);
  while (i < m && j < n) {
    if (j == -1 || S[i] == T[j]) {
      i++;j++;
    }
    else
      j = next[j];
  }
  if (j == n)
    return i-n; // 匹配成功，返回匹配发生在主串的下标位置
  else
    return -1; // 匹配失败
}

int main() 
{ 
  //char txt[] = "ABABDABACDABABCABAB"; 
  //char pat[] = "ABAB";
  int idx=-1;
  char S[] = "ABC ABCDAB ABCDABCDABDE"; 
  char T[] = "ABCDABD";
  //char T2[] = "abcabaa";
  char T2[] = "cddcdececdea";
  int next[strlen(T2)];
  idx = KMP(S, T, strlen(S), strlen(T));
  printf("%d\n", idx);
  Next(T2,next,strlen(T2));
  for (int w=0; w<strlen(T2); w++) printf("%3d", next[w]);
  return 0; 
} 


/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Sat Nov  16 21:32:56 2024              *
 * Last Modify:                                        *
 * Comment: 模式匹配，即字符串查找的朴素算法改进版本，能够输 *
 * 出每次子串出现的位置，可以利用这个扩展版本进行字符串的替换 *
 * 操作，比如HW5的作业中可以用这里的扩展版展开解体思路       *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void BF_extend(char *S, char *T) {
  int i, j, m = strlen(T), n = strlen(S);
  i = j = 0;
  while (i < n) {
    while (j < m && S[i] == T[j]) {
      i++;
      j++;
    }

    if (j == m) printf("%d\n", i - m);
    i = i-j+1;
    j = 0;
  }
}


int main()
{
  char S[30] = "abcdefghijklmnghij", T[10] = "ghij";

  BF_extend(S, T);

  return 0;
}

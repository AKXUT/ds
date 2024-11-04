/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Sat Nov  2 21:32:56 2024               *
 * Last Modify:                                        *
 * Comment: 模式匹配，即字符串查找的朴素算法               *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int BF(char *S, char *T) {
  int i, j, m = strlen(T), n = strlen(S);
  i = j = 0;
  while (i < n && j < m) {
    if (S[i] == T[j]) {
      i++;
      j++;
    }else {
      i = i-j+1;   // i 退回到本次匹配首位的下一个位置
      j = 0;	   // j 退回到模式串 T 的首位
    }
  }
  if (j == m) return i - m;   // 匹配成功
  else        return -1;      // 匹配失败
}


int main()
{
  char S[30] = "abcdefghijklmn", T[10] = "ghij";
  int rst; 

  rst = BF(S, T);

  if (rst == -1) printf("not found!\n");
  else           printf("found at %d\n", rst);

  return 0;
}

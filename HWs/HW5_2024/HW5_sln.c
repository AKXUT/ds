#include<stdio.h>
#include<string.h>
int BF(char *S, char *T) {
    int i, j, m = strlen(T), n = strlen(S);
    i = j = 0;
    while (i < n && j < m) {
        if (S[i] == T[j]) {   i++;    j++;  }
        else {
            i = i-j+1; // i 退回到本次匹配首位的下一个位置
            j = 0;       // j 退回到模式串 T 的首位
        }
    }
    if (j == m)       return i - m; // 匹配成功
    else              return -1;      // 匹配失败
}

int stringmatch(char *S, char *T, char *rep, char *ans) {
  int curr_found, last_found = -1, k=0, j;
  while ((curr_found = BF(S + last_found + 1, T)) != -1) {
    curr_found = last_found + curr_found +1;
    if (last_found == -1)  j = 0;
    else j = last_found + strlen(T);
    for (; j < curr_found; j++)
      ans[k++] = S[j];
    strcat(ans+k,rep);
    k += strlen(rep) ;
    last_found = curr_found;
  }
  if (last_found == -1) return 0;
  strcat(ans + k, S + last_found + strlen(T));
  return 1;
}


int main()
{
    int found = 0;
    //char S[100] = "abc--abc--abc", T[100] = "--", rep[100] = "p", ans[100] = {0};
    /*
    printf("\n 请输⼊主串:");
    gets(S);
    printf("\n 请输⼊模式串:");
    gets(T);
    printf("\n 请输⼊替换串:");
    gets(rep);
    */
    found = stringmatch(S, T, rep, ans);
    if(found) printf("\n 最终结果是 %s", ans);
    else printf("\n 未能匹配模式串");
}

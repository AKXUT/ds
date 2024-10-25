/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Fri Oct 25 18:24:38 2024               *
 * Last Modify:                                        *
 * Comment: 从键盘输入字符串，以遇到一个特殊字符为结束标志， *
 *          要求逆序输出该字符串（不包括该特殊字符），用递归 *
 *          函数实现。                                  *
 ******************************************************/

#include <stdio.h>

void ReverseInput() {
  char ch = getchar();
  if (ch == '#')
    return;

  ReverseInput();
  putchar(ch);
}

int main()
{
  ReverseInput();
  return 0;
}

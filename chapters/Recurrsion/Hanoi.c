/*********************************************************
 * Author:       David  Song                              *
 * Mail:         songxin@xaut.edu.cn                      *
 * Create Date: Sat Nov  9 12:02:45 2024                  *
 * Last Modify:                                           *
 * Comment: a recursive function to move the hanoi tower  *
 ******************************************************/

#include <stdio.h>

void move(char from, char to, char by, int n) {
  if (n == 1) {
    printf("%c -> %c\n", from, to);
    return;
  }
  else {
    move(from, by, to, n - 1);
    printf("%c -> %c\n", from, to);
    move(by, to, from, n - 1);
  }
}

int main()
{
  move('A', 'B', 'C', 3);
  return 0;
}

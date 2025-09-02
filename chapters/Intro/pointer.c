






/*************************************************
 * Created by David on Tue Sep  2 15:10:57 2025  *
 *************************************************/

#include <stdio.h>

int addone(int a) {
  a++;
  return a;
}

void addone2(int *a) {
  (*a)++;
}

int main() {
  /*
  int x = 3, *p, **q;
  p = &x;
  q = &p;
  printf("%x\n", p);
  printf("%x\n", q);
  printf("%d\n", sizeof(int));*/
  int x = 3;
  // x = addone(x);
  addone2(&x);
  printf("%d\n", x);
  return 0;
}

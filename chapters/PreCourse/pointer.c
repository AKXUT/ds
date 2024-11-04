#include<stdio.h>
typedef struct {
  int x;
  int y;
  char color;
}PT;

int main(){
  PT p1 = {3, 5, 'r'}, *p;
  p = &p1;
  printf("%d, %d, %c\n", (*p).x, p->y, p1.color);

  printf("%x\n", p);
  printf("%x\n", &p);
  return 0;
}

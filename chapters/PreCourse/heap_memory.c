#include <stdio.h>
#include <stdlib.h>

void fun(int **q);
int * fun2();
void createIntArray(int **q, int n);
  
int main()
{
  int a = 5;
  int *b, *c;

  //fun(&b); // &b 是一个二级地址
  b = fun2();
  printf("%d, %d\n", a, *b);

  createIntArray(&c, 10);

  for (int i = 0; i < 10; i++)
    c[i] = i + 1;

  for (int i = 0; i < 10; i++)
    printf("%d ", c[i]);
  
  return 0;
}

// 形参q 是个二级指针变量
void fun(int **q) {
  (*q) = (int *)malloc(4); // 写成(*q) = (int *)malloc(sizeof(int)); 更正规
  *(*q) = 10;
}


int * fun2() {
  int *tmp;
  tmp = (int*)malloc(sizeof(int));
  *tmp = 20;
  return tmp;
}

// 动态一维整型数组创建，n是需要创建数组的大小
void createIntArray(int **q, int n) {
  *q = (int *) malloc(n * sizeof(int)); //在内存的堆区申请了n个整数大小的空间，这个空间的首地址通过赋值语句传递给*q，本质上是赋值给了主函数的变量c
}

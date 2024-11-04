/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Mon Nov  4 23:11:25 2024                *
 * Last Modify:                                        *
 * Comment:                                            *
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
typedef char ElemType;
typedef struct seqQue {
  ElemType a[MAX];
  int front;
  int rear;
} Que;

void InitQue(Que **p) {
  *p = malloc(sizeof(Que));
  (*p)->front = 0;
  (*p)->rear  = 0;
}

int QueEmpty(Que *p) {
  return p->front == p->rear;
}

int QueFull(Que *p) {
  return (p->rear + 1) % MAX == p->front;
}

void EnQue(Que *p, ElemType x) {
  // printf("p->front: %d, p->rear: %d\n", p->front, p->rear);
  if (QueFull(p))
    puts("error: enqueue to a full queue!");
  else {
    p->a[p->rear] = x;
    p->rear = (p->rear + 1) % MAX;
  }
}

void DeQue(Que *p, ElemType *q) {
  if (QueEmpty(p))
    puts("error: depart from an empty queue!");
  else {
    *q = p->a[p->front];
    p->front = (p->front + 1) % MAX;
  }
}

void PrintQue(Que *p) {
  if (QueEmpty(p)) return;
  puts("the queue has: ");
  int i = (p->front + 1) % MAX;
  while (i != p->rear) {
    printf("%5c", p->a[i]);
    i = (i + 1) % MAX;
  }
  printf("%5d\n", p->a[i]);
}

void QueClear(Que *p) {
  p->front = p->rear = 0;
}

void QueDestory(Que **p) {
  free(*p);
  *p = NULL;
}

// HW4 required function
char fun(char *str) {
  int i = 0, diff = 0;
  char ch;
  Que *Q;
  InitQue(&Q);
  while ((ch = str[i++]))
    if (ch != ':')
      EnQue(Q, ch);
    else
      break;

  if (!str[i-1]) // there is no : in the string
    return 'N';

  while (!QueEmpty(Q) && str[i]) {
    DeQue(Q, &ch);
    if (ch != str[i])
      diff = 1;
    i++;
  }
  if (!QueEmpty(Q)) return 'L';
  else if (str[i])   return 'R';
  else if (diff)     return 'D';
  else               return 'S';
}


int main()
{
  // char input[50] = "Sample:Sample";
  // char input[50] = "abc:ple";
  // char input[50] = "axyz:xyz";
  char input[50] = "xyz:xyzb";
  // char input[50] = "Sample:Sample";
  // char input[50] = "Sample:Sample";
  printf("%c\n", fun(input));
  return 0;
}

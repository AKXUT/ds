/************************************************
 Created by David Song in 2016-4-28

 Note:
   1. Link list implementation of stack
   2. Use link stack to help calculate postfix
      expressions
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum relation{ADD, SUB, MUL, DIV, LF, RT, AMP};

int RelMat[7][7] = {{ 1,  1, -1, -1, -1, 1, 1},
		    { 1,  1, -1, -1, -1, 1, 1},
		    { 1,  1,  1,  1, -1, 1, 1},
		    { 1,  1,  1,  1, -1, 1, 1},
		    {-1, -1, -1, -1, -1, 0, 7},
		    { 1,  1,  1,  1,  7, 1, 1},
		    {-1, -1, -1, -1, -1, 7, 0}};

// 任务1，在这里补充链式栈的类型定义和操作函数
// 设计了一个不带头结点的链栈，存储元素类型为整数

#define MAX 100
typedef int ElemType;  // 整型元素链栈

typedef struct node {
  ElemType data;
  struct node *next;
}Node;

// 因为采用了不带头结点的链栈，因此采用了二级指针
void InitStack(Node **p) {
  *p = NULL;
}

int StackEmpty(Node *p) {
  return p == NULL ? 1 : 0;
}

// 因为采用了不带头结点的链栈，因此采用了二级指针
// 因为链栈本质上是线性表，入栈操作是在线性表的开头，
// 相当于头插法，所以每次入栈后，栈的开头指针都指向了
// 新元素，所以每次入栈都要修改栈顶指针。

void Push(Node **p, ElemType x) {
  Node *s = malloc(sizeof(Node));
  s->data = x;
  s->next = (*p);
  *p = s;
}

// pop 也需要使用二级指针，因为每次pop都修改了栈顶指针
void Pop(Node **p, ElemType *q) {
  Node *p_saved = *p;
  if (!StackEmpty(*p)) {
    *q = (*p)->data;
    *p = (*p)->next;
    free(p_saved);
  }
}

int StackTop(Node *p, ElemType *q) {
  if (!StackEmpty(p)) {
    *q = p->data;
    return 1;
  }
  else
    return 0;
}

void StackDestory(Node **p) {
  Node *tmp;
  while (!StackEmpty(*p)) {
    tmp = *p;
    *p = (*p)->next;
    free(tmp);
  }
  *p = NULL;
}



// 任务2，补充Calc函数体
int Calc(char *s) {
// 注意计算时，最好用一个整数型的栈，字符数字入栈前，先转换为整数（即减去'0'）再入栈
  Node *p;
  int rst, left, right;
  char ch;
  InitStack(&p);
  
  while ((ch=*s) != '\0') {
    if (ch >= '1' && ch <= '9')  Push(&p, ch - '0');
    else {
      Pop(&p, &right);
      Pop(&p, &left);
      switch (ch) {
      case '+': Push(&p, left + right); break;
      case '-': Push(&p, left - right); break;
      case '*': Push(&p, left * right); break;
      case '/': Push(&p, left / right); break;
      }
    }
    s++;
  }
  StackTop(p, &rst);
  return rst;
}

int idx(char x) {
  switch (x) {
  case '+' : return 0;
  case '-' : return 1;
  case '*' : return 2;
  case '/' : return 3;
  case '(' : return 4;
  case ')' : return 5;
  case '#' : return 6;
  default: return -1;
  }
}

int compare(char a, char b) {
  return RelMat[idx(a)][idx(b)];
}

// 中缀转后缀
void InfixToPostfix(char in[], char post[]) {
  int ch, tmp, j = 0;;
  Node *s;
  int i = 0;
  ch = in[i];
  InitStack(&s);
  Push(&s, '#');
  StackTop(s, &tmp);
  
  while (ch != '\0') {
    if (ch >= '0' && ch <= '9') {
      post[j++] = ch;
      ch = in[++i];
    }
    else {
      StackTop(s, &tmp);
      while (compare(tmp, ch) == 1) {
	Pop(&s, &tmp);
	post[j++] = tmp;
	StackTop(s, &tmp);
      }
      if (compare(tmp, ch) == -1) {
	Push(&s, ch);
	ch = in[++i];
      }
      else {
	Pop(&s, &tmp);
	ch = in[++i];
      }
    }

  }
}

int main() {
  //  中缀： (5+3)*2+(6+3)  计算结果：25
  //  后缀： 53+2*63++

  //  中缀： 9-6/3 计算结果 7
  //  后缀： 963/- 

  char in[50] = "9-6/3#", post[50] = {0};
  // char in[50] = "(5+3)*2+(6+3)#", post[50] = {0};
  InfixToPostfix(in, post);
  puts(in);
  puts(post);
  printf("the results is: %d\n", Calc(post));
  return 0;
}

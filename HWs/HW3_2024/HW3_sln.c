/*************************************************************
 * Created by David Song in 2016-4-26                        *
 * Updated by David Song in 2019-9-12                        *
 * Solved  by David Song in 2024-11-3                        *
 * 提问：你能从函数的首行定义中看出，调用初始化函数的调用方，       *
 *       应该准备什么样的变量吗？                               *
 *                                                           *
 * Note:                                                     *
 *   1. Sequencial implementation of stack                   *
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef char ElemType;
typedef struct stack {
  ElemType a[MAX];
  int top;
} Stack;

void InitStack(Stack *p) {
  p->top = -1;
}

int StackEmpty(Stack *p) {
  return p->top == -1;
}

int StackFull(Stack *p) {
  return p->top == MAX - 1;
}

void Push(Stack *p, ElemType x) {
  if (StackFull(p)) {
    printf("stack full\n");
    return;
  }
  p->top++;
  p->a[p->top] = x;
}

void Pop(Stack *p, ElemType *q) {
  if (StackEmpty(p)) {
    printf("stack empty! Can not pop!\n");
    return;
  }
  *q = p->a[p->top--];
}

void StackTop(Stack *p, ElemType *q) {
  if (StackEmpty(p)) {
    printf("stack empty! Can not pop!\n");
    return;
  }
  *q = p->a[p->top];
}

void StackClear(Stack *p) {
  p->top = -1;
}

// 待判断的字符串保存在数组a中，数组的有效长度保存在n中
// 通过计算返回0，表示括号不匹配，返回1表示匹配
int Match(char *str) {
  char ch;
  int i;
  Stack S;
  
  InitStack(&S);
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == '{' || str[i] == '[' || str[i] == '(')
      Push(&S, str[i]);
    else if (str[i] == '}' || str[i] == ']' || str[i] == ')') {
      if (!StackEmpty(&S)) { // 非栈空
	StackTop(&S, &ch);
	if ((ch == '(' && str[i] == ')') ||
	    (ch == '[' && str[i] == ']') ||
	    (ch == '{' && str[i] == '}') )
	  Pop(&S, &ch);
	else     break;
      }
      else  break; // 栈空
    }
  } // for 结束
  return (i == strlen(str)) && StackEmpty(&S);
} // Match结束

int main() {
  char str[100] = "()[]{}";
  //char str[100] = "{[()][(()())]}";
  //char str[100] = "([)]{}";
  //char str[100] = "{[)(]{}}";

  printf("%d\n", Match(str));
  return 0;
}        

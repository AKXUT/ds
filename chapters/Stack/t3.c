/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Mon Sep 26 15:58:17 2022               *
 * Last Modify:                                        *
 * Comment: 判断用户输入的序列是否为一个合法的出栈序列      *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 20

typedef char DataType;

typedef struct { DataType data[MAXSIZE]; int top;} SeqStack;

SeqStack* InitStack() { //初始化栈s，置为空栈
  SeqStack* s;
  s=(SeqStack*)malloc(sizeof(SeqStack));
  s->top = -1;
  return s;
}

//判断s是否为空栈，若为空栈，返回1，否则返回0
int StackEmpty(SeqStack  *s) { return  s->top==-1; }

int Push(SeqStack *s, DataType x) {
  if(s->top==MAXSIZE-1) { //栈满
    printf ("栈已满!\n");
    return 0;       //入栈失败返回0
  }
  s->top++;        //栈顶指针增加1
  s->data[s->top]=x;  //将新元素赋值给栈顶空间
  return 1;            //入栈成功返回1
}

int Pop(SeqStack *s,  DataType *px) {
  if(StackEmpty(s)) {
    printf ("栈空!\n");
    return 0;         //出栈失败返回0
  }
  *px=s->data[s->top];  // 将栈顶元素赋值给px指向的变量
  s->top--;                // 栈顶指针减1
  return  1;           //出栈成功返回1
}

int GetTop(SeqStack *s,DataType *px) {
  if(StackEmpty(s)) {
    printf ("栈空!\n");
    return 0;         //读取栈顶元素失败返回0
  }
  *px=s->data[s->top];  // 将栈顶元素赋值给px指向的变量
  return  1;           //读栈顶元素成功返回1
}

int JudgeSerial(char str[], int n) { //若长度为n的字符序列str对应的是正确的出栈序列，返回1；否则返回0
  SeqStack* s = InitStack(); //s为顺序栈指针
  char x, *c = malloc(sizeof(char) * n);   //c用于保存进栈的字符序列
  
  int i = 0, j = 0; //i,j分别用于控制在字符序列c和str中的当前扫描位置
  for (i = 0; i < n; i++) c[i] = 65 + i; // 初始化填充入栈元素序列
  
  for (i = 0; i < n; i++) {
    Push(s, c[i]);
    while (!StackEmpty(s) && j < n && s->data[s->top] == str[j]) {
      Pop(s, &x);
      j++;
    }
  }
  return j == n;
}

int main() {
  char str[MAXSIZE];
  
  //输入待判断的字符序列
  scanf("%s",str);
  if(JudgeSerial(str,strlen(str)))
    printf("%s : 是一个正确的出栈序列\n",str);
  else
    printf("%s : 不是一个正确的出栈序列\n",str);
  return 0;
}

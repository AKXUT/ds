/*******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Mon Oct 21 07:34:21 2024               *
 * Last Modify:                                        *
 * Comment: 多项式加法                                  *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define M 12  // 数组 a 的大小
#define N 8   // 数组 b 的大小

// 在这里补充一个结构体定义，包括系数和指数两项内容，同时为该结构体定义一个类型别名 ElemType
typedef struct {
  int coef; // 系数
  int expo; // 指数
} ElemType; // 类型别名

// 这是顺序表的结构体定义
typedef struct list {
  ElemType data[MAXSIZE + 1];
  int len;
} SeqList;

SeqList * InitList();
void InitList2(SeqList **ppList);
int ListFull(SeqList *pList);
int ListEmpty(SeqList *pList);
int ListLen(SeqList *pList);
void Error(char *msg);
int GetElem(SeqList *pList, int i, ElemType *pElm);
int InsertElem(SeqList * pList, int i, ElemType elm);
int DelElem(SeqList *pList, int i, ElemType *pElm);
void PrintList(SeqList *pList);


int main() {
  int i, j, k;
  // A, B, C 指向顺序表结构体的指针
  SeqList *A, *B, *C;

  // 下面的数组 a 和 b 记录了两个多项式的信息，它们是原始的输入数据，
  // 数组中的数据是多项式系数，它们在数组中的下表位置表示次方，
  // 例如数组 a 记录的多项式如下：
  // 0*X^0 + 0*X^1 + 7*X^2 + 0*X^3 + 3*X^4 + 1*X^5 + 9*X^6 + ...
  // 数组 b 记录的多项式如下：
  // 0*X^0 + 0*X^1 + 8*X^2 + 1*X^3 + 22*X^4 + 7*X^5 ...
  int a[M] = {0, 0, 7,0,3,1,9,8,5,17,-8,100}, b[N] = {0, 0, 8,1,22,7,-9, 8};

  ElemType temp;
  ElemType elemFromA, elemFromB;
  
  // 请将你补充的代码写在这里，
  // 1. 初始化 A, B, C三个顺序表
  // 2. 完成从 a 数组读入不为零的数据，创建ElemType的项数据，然后逐个插入到 A 顺序表
  // 3. 完成从 b 数组读入不为零的数据，创建ElemType的项数据，然后逐个插入到 B 顺序表
  // 4. 将 A 和 B 两个顺序表中保存的多项式进行相加，结果保存在 C 顺序表

  InitList2(&A);
  InitList2(&B);
  InitList2(&C);

  for (i = 0; i < M; i++) {
    if (a[i]) {
      temp.coef = a[i];
      temp.expo = i;
      InsertElem(A, A->len+1, temp); 
    }
  }

  for (i = 0; i < N; i++) {
    if (b[i]) {
      temp.coef = b[i];
      temp.expo = i;
      InsertElem(B, B->len+1, temp); 
    }
  }

  i = j = k = 1;
  while (i <= A->len && j <= B->len) {
    GetElem(A, i, &elemFromA);
    GetElem(B, j, &elemFromB);
    if (elemFromA.expo < elemFromB.expo) {
      InsertElem(C, C->len+1, elemFromA);
      i++;
    }
    else if (elemFromA.expo > elemFromB.expo) {
      InsertElem(C, C->len+1, elemFromB);
      j++;
    }
    else {
      i++; j++;
      if (elemFromA.coef + elemFromB.coef == 0)
	continue;
      else {
	temp.coef = elemFromA.coef + elemFromB.coef;
	temp.expo = elemFromA.expo;
	InsertElem(C, C->len+1, temp);
      }
    }
  }

  while (i <= A->len) {
    GetElem(A, i++, &elemFromA);
    InsertElem(C, C->len+1, elemFromA);
  }
  while (j <= B->len) {
    GetElem(B, j++, &elemFromB);
    InsertElem(C, C->len+1, elemFromB);
  }

  PrintList(C);
  return 0;
}


/* 输入：无
   返回：指向顺序表的指针，通过返回值，把申请到的、指向内存空间的指针带回调用方。
   功能：为顺序表申请内存空间，并把顺序表的大小置为0。
*/
SeqList * InitList() {
  SeqList *pList;
  pList = (SeqList *)malloc(sizeof(SeqList));
  pList->len = 0;
  return pList;
}

/* 输入：指向顺序表结构体的二级指针，调用方需要准备一个顺序表指针变量，然后把该
         变量的地址传递进来（即一个二级地址）
   返回：无
   功能：为顺序表申请内存空间，并把顺序表的大小置为0。
*/
void InitList2(SeqList **ppList) {
  *ppList = (SeqList *)malloc(sizeof(SeqList));
  (*ppList)->len = 0;
}

/* 输入：指向顺序表的指针
   返回：返回整型变量1，表示顺序表已满，否则未满。
   功能：判断顺序表是否已满。
*/
int ListFull(SeqList *pList) {
  return (pList->len == MAXSIZE) ? 1 : 0;
}

/* 输入：指向顺序表的指针
   返回：返回整型变量1，表示顺序表是空表，否则非空。
   功能：判断顺序表是否已空。
*/
int ListEmpty(SeqList *pList) {
  return (pList->len == 0) ? 1 : 0;
}

/* 输入：指向顺序表的指针
   返回：返回整型变量，表示顺序表有效元素个数
   功能：提供顺序表有效元素个数
*/
int ListLen(SeqList *pList) {
  return pList->len;
}

/* 输入：字符指针
   返回：无
   功能：输出自定义的出错消息定义
*/
void Error(char *msg) {
  printf("[错误]：%s\n", msg);
}

int GetElem(SeqList *pList, int i, ElemType *pElm) {
  if (ListEmpty(pList)) {
    Error("从空表中读取数据元素");
    return 0;
  }
  if (i < 1 || i > MAXSIZE) {
    Error("读取位置错误！");
    return 0;
  }
  *pElm = pList->data[i];
  return 1;
}

int InsertElem(SeqList * pList, int i, ElemType elm) {
  int k;
  if (ListFull(pList)) {
    Error("无法向已经满了的顺序表插入数据元素!");
    return 0;
  }
  if (i < 1 || i > pList->len + 1) {
    Error("插入位置越界!");
    return 0;
  }
  for (k = pList->len; k >= i; k--)
    pList->data[k + 1] = pList->data[k];
  pList->data[i] = elm;
  pList->len += 1;
  return 1;
}

void PrintList(SeqList *pList) {
  int i;
  for (i = 1; i <= pList->len; i++)
    // 添加一条 printf 打印语句，输出顺序表第 i 项的系数和指数
    // 例如：34*X^5，即34乘以X的5次方
    // 输出为：(34, 5)
    printf("(%d, %d) ", pList->data[i].coef, pList->data[i].expo);
  putchar('\n');
}

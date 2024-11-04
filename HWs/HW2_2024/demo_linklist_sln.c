/* Copyright[2021] David */
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct node {
  ElemType elm;
  struct node *next;
}SLNode;

void ListInit(SLNode **ppHead) {
  (*ppHead) = (SLNode*)(malloc(sizeof(SLNode)));
  (*ppHead)->next = NULL;
}

/* 输入：指向头结点的一级指针
   返回：链表中元素的个数
   功能：计算链表中元素的个数
*/
int ListLen(SLNode *pHead) {
  SLNode *p = pHead;
  int len = 0;
  
  while (p->next) {
    p = p->next;
    len++;
  }
  return len;
}

/* 输入：指向头结点的一级指针，插入位置、插入数据
   返回：函数返回0表示元素插入成功，返回1表示元素插入失败
   功能：为插入数据elem创建一个新的节点，然后把该节点插入到i位置
        原来i位置的节点将变为i+1位置的节点
*/
int ListInsert(SLNode *pHead, int i, ElemType elm) {
  SLNode *s, *p = pHead;
  int len = ListLen(pHead);
  
  if (i < 0 || i > len + 1) {
    printf("illeagal insertion position at %d with list length %d\n", i, len);
    return 1;
  }

  int j = 0;
  while (p && j < i - 1) {
    p = p->next;
    j++;
  }
  
  s = (SLNode *)malloc(sizeof(SLNode));
  s->elm = elm;
  s->next = p->next;
  p->next = s;
  return 0;
}

/* 输入：指向头结点的一级指针，删除位置、指向ElemType的一级指针
   返回：函数返回0表示元素删除成功，返回1表示元素删除失败
   功能：把位于i位置的节点删除，同时把该节点中保存的data数据通过pElem指针间接访问，
        带回给本函数的调用方，并释放该节点占用的堆区内存，原来i+1位置的节点将变为i位置的节点
*/
int ListDelete(SLNode *pHead, int i, ElemType *pElm) {
  SLNode *r, *p = pHead;
  int len = ListLen(pHead);

  if (i < 1 || i > len) {
    printf("illeagal deletion position at %d with list length %d\n", i, len);
    return 1;
  }
  
  int j = 0;
  while (p && j < i - 1) {
    p = p->next;
    j++;
  }
  r = p->next;
  *pElm = r->elm;
  p->next = r->next;
  free(r);
  return 0;
}

/* 输入：指向头结点的一级指针，指向ElemType的一级指针
   返回：函数返回0表示元素获取成功，返回1表示元素获取失败
   功能：把位于i位置的节点中的data拷贝一份给*pElem
*/
int ListGet(SLNode *pHead, int i, ElemType *pElm) {
  SLNode *p = pHead;
  int len = ListLen(pHead);

  if (i < 1 || i > len) {
    printf("illeagal deletion position at %d with list length %d\n", i, len);
    return 1;
  }
  for (int j = 0; j < i; j++)
    p = p->next;
  *pElm = p->elm;
  return 0;
}

/* 输入：指向头结点的二级指针
   返回：无返回值
   功能：把*ppHead所指的链表中的元素，逐个地删除和释放，
        最后把*ppHead一级指针设置为空值
*/
void ListDestroy(SLNode **ppHead) {
  SLNode *r;

  while ((*ppHead)->next) {
    r = (*ppHead)->next;
    *ppHead = (*ppHead)->next;
    free(r);
  }
}

/* 输入：指向头结点的一级指针
   返回：无返回值
   功能：把*ppHead所指的链表中的元素，逐个地打印到控制台（即屏幕输出），
*/
void ListPrint(SLNode *pHead) {
  SLNode *p = pHead->next;
  while (p) {
    printf("%d ", p->elm);
    p = p->next;
  }
  putchar('\n');
}

// main函数对以上单链表操作进行测试
int main() {
  int i;
  ElemType a[10], b[10], x;
  SLNode *pHead;
  for (i = 0; i < 10; i++) {
    b[i] = 100 + i;
    a[i] = i + 1;
  }
  ListInit(&pHead);
  for (i = 0; i < 10; i++)
    ListInsert(pHead, i + 1, a[i]);
  puts("把a数组中的所有元素插入到链表pHead后的结果：");
  ListPrint(pHead);
  for (i = 0; i < 10; i++)
    ListInsert(pHead, i + 1, b[i]);
  puts("把b数组中的所有元素继续插入到链表pHead后的结果：");
  ListPrint(pHead);
  for (i = 0; i < 10; i++) {
    ListDelete(pHead, 1, &x);
    printf("删除了：%d\n", x);
  }
  puts("把链表删除一部分后，继续打印结果：");
  ListPrint(pHead);

  return 0;
}


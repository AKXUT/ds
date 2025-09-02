/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Sat Nov  2 16:20:55 2024               *
 * Last Modify:                                        *
 * Comment: 关于排序二叉树BST的各种操作的实验              *
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct node{
  DataType data;
  struct node *lchild;
  struct node *rchild;
} BSTNode;

BSTNode * BST_Insert(BSTNode **root, DataType x) {
  BSTNode *curr, *parent = NULL, *p;
  curr = *root;
  while(curr != NULL) {
    if(curr->data == x) return NULL;
    parent = curr;
    if(curr->data < x) curr = curr->rchild;
    else               curr = curr->lchild;
  }
  /*生成新结点*/
  p = (BSTNode *)malloc(sizeof(BSTNode));
  p->data = x;
  p->lchild = NULL;
  p->rchild = NULL;

  if(parent == NULL) *root = p;
  else if(x < parent->data) parent->lchild = p;
  else                      parent->rchild = p;
  return p;

}

BSTNode * BST_Search(BSTNode *root, DataType x) {
  BSTNode *p;
  if(root != NULL)  {
    p = root;
    while(p != NULL) {
      if(p->data == x) return p;
      if(p->data < x)  p = p->rchild;
      else             p = p->lchild;
    }
  }
  return NULL;	
} 

BSTNode * BST_Create(DataType a[], int n) {
  BSTNode *root = NULL;
  int i;
  for (i = 0; i < n; i++) 
    BST_Insert(&root, a[i]);
  return root;

}

void PreOrder(BSTNode *root, void (*visit)(DataType)) {
  if (root) {
    visit(root->data);
    PreOrder(root->lchild, visit);
    PreOrder(root->rchild, visit);
  }
}

void PostOrder(BSTNode *root, void (*visit)(DataType)) {
  if (root) {
    PostOrder(root->lchild, visit);
    PostOrder(root->rchild, visit);
    visit(root->data);
  }
}

void InOrder(BSTNode *root, void (*visit)(DataType)) {
  if (root) {
    InOrder(root->lchild, visit);
    visit(root->data);
    InOrder(root->rchild, visit);
  }
}

void ReverseOrder(BSTNode *root, void (*visit)(DataType)) {
  if (root) {
    ReverseOrder(root->rchild, visit);
    visit(root->data);
    ReverseOrder(root->lchild, visit);
  }
}



void PrintData(DataType x) { printf("%d ", x); }

void PrintTree(BSTNode *root, int n) {
  int i;  // n表示bt指向的节点所在的层数
  if(root == NULL) return;
  PrintTree(root->rchild, n+1);
  for(i = 0; i < n-1; i++) printf("   "); // 打印3个空格
  if(n > 0) {  printf("---");  printf("%d\n", root->data); }
  PrintTree(root->lchild, n+1);
}


int main()
{
  BSTNode *root;
  //DataType a[8] = {1,2,3,4,5,6,7,8};
  //DataType a[8] = {8,7,6,5,4,3,2,1};
  //DataType a[8] = {7,8,6,5,1,3,4,2};
  DataType a[8] = {3,1,6,5,4,7,8,2};

  root = BST_Create(a, 8);
  InOrder(root, PrintData);
  putchar('\n');
  ReverseOrder(root, PrintData);
  putchar('\n');
  PrintTree(root, 1);
  
  return 0;
}

  

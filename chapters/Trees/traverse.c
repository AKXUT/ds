/**
 * Created by David on Fri Apr 22 20:06:27 2022
 *
 * Descretption: traverse of binary tree
 *
 * Last Modified: 
 */

#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct node {
  DataType data;
  struct node * left;
  struct node * right;
}BSTree;

void myprint(BSTree *p) {
  printf("%c ", p->data); 
}

void myprint2(BSTree *p) {
  printf("%c ", p->data - 32); 
}

void mychange(BSTree *p) {
  p->data++;
}

void InOrder(BSTree *root, void (*visit)(BSTree *)) {
  if( root ){
    InOrder(root->left, visit);     //中序遍历左子树
    visit(root);   //遍历根结点
    InOrder(root->right, visit);     //中序遍历右子树
  }
}

// 通过字符串(用户键盘输入)创建二叉树的函数
void MakeCharTree(BSTree **bt) {
  char ch;
  ch = getchar();
  if (ch == '$') *bt = NULL;
  else {
    *bt = (BSTree*)malloc(sizeof(BSTree));
    (*bt)->data = ch;
    MakeCharTree(&((*bt)->left));
    MakeCharTree(&((*bt)->right)); } // else ends
}   // function ends

int main()
{
  BSTree *root;
  MakeCharTree(&root);
  InOrder(root, myprint);
  putchar('\n');
  InOrder(root, myprint2);
  putchar('\n');
  InOrder(root, mychange);
  InOrder(root, myprint);
  putchar('\n');

  return 0;
}

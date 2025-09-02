/******************************************************
 * Created by David Song in 2016-5-14
 *
 * Note:
 *   1. use a MakeCharTree to build a bi-tree by a 
 *      string which is in pre-order sequence without a
 *      head node
 *   2. update this bi-tree to a threaded binary tree
 *   3. visit each tree element by loop through the
 *      threaded bi-tree
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char DataType;

typedef struct treenode {
  DataType data;
  struct treenode * leftChild;
  struct treenode * rightChild;
  // 线索标志，为0时表示leftChild是孩子指针，为1时表示leftChild是线索指针
  int leftThread;
  // 线索标志，为0时表示rightChild是孩子指针，为1时表示rightChild是线索指针
  int rightThread;
}TreeNode;

#define Link 0
#define Thread 1

TreeNode *pre;  // 当前节点的前驱节点的指针

/* 二叉树的线索化 */
void InThread(TreeNode *p) {
  if (p == NULL) return;
  InThread(p->leftChild);
  // 处理当前节点的做孩子指针
  if (p->leftChild != NULL)
    p->leftThread = Link;
  else {
    p->leftThread = Thread;
    p->leftChild = pre;
  }
  // 处理前一个（中序）节点的右孩子指针
  if (pre->rightChild != NULL)
    pre->rightThread = Link;
  else {
    pre->rightThread = Thread;
    pre->rightChild = p;
  }
  // 当前的孩子被更新为前一个孩子
  pre = p;
  InThread(p->rightChild);
}

/* InThread_Wrap函数的任务有两个：
 * 1. 二叉树的线索化
 * 2. 添加头指针及其内部数据
 *
 * 二叉树的线索添加工作，由InThread函数完成，在此处只是调用
 * 添加头结点及其内部成员数据，由InThread_Wrap函数自己完成
 */
void InThread_Wrap(TreeNode **p, TreeNode *root) {
  *p = malloc(sizeof(TreeNode));
  (*p)->leftThread = Link;
  (*p)->rightThread = Thread;
  (*p)->rightChild = *p;
  if (root == NULL)
    (*p)->leftChild = *p;
  else {
    (*p)->leftChild = root;
    pre = *p;
    InThread(root);
    pre->rightChild = *p;
    pre->rightThread = Thread;
    (*p)->rightChild = pre;
  }
}

/* 该函数输入一个先序遍历的二叉树序列，序列中的空指针用$符号代替
 * 例如：ABD$$EH$$$CF$I$$G$$
 */
void MakeCharTree(TreeNode **bt) {
  char ch;
  ch = getchar();
  if (ch == '$') {
    *bt = NULL;
  }
  else {
    *bt = (TreeNode*)malloc(sizeof(TreeNode));
    (*bt)->data = ch;
    MakeCharTree(&((*bt)->leftChild));
    MakeCharTree(&((*bt)->rightChild));
  }
}

void Print(TreeNode * pNode) {
  printf("%c ", pNode->data);
}

/* 利用递归函数输出二叉树的中序遍历序列 */
void RecInOrder(TreeNode *t, void (*visit)(TreeNode * pNode)) {
  if (t != NULL) {
    RecInOrder(t->leftChild, visit);
    visit(t);
    RecInOrder(t->rightChild, visit);
  }
}

/* 利用中序线索二叉树中的线索指针，中序遍历二叉树 */
void ThreadInOrder(TreeNode *r) {
  TreeNode *p;

  p = r->leftChild;  // p指向根结点
  while (p != r) {  // 空树或遍历结束时p == r
    while (p->leftThread == Link)  // 当一直有左孩子节点时，一路向左直到叶子节点
      p = p->leftChild;
    printf("%c ", p->data);  // 显示结点数据，可以更改为其他对结点的操作
    while (p->rightThread == Thread && p->rightChild != r) {
      p = p->rightChild;
      printf("%c ", p->data);
    }
    p = p->rightChild;  // p进入其右子树
  }
}

int main(void) {
  TreeNode *root, *root2;
  MakeCharTree(&root);
  // 利用递归函数输出二叉树的中序遍历序列
  puts("二叉树中序遍历：");
  RecInOrder(root, Print);
  putchar('\n');

  // 对没有头结点的二叉树root进行线索化
  InThread_Wrap(&root2, root);

  // 利用二重循环输出中序线索二叉树的遍历序列
  puts("二叉树中序遍历：");
  ThreadInOrder(root2);
  return 0;
}

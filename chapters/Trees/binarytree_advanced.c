/******************************************************
 * Created by David Song in 2016-5-14
 *
 * Note:
 *   1. use MakeCharTree function to build a bi-tree
 *      by adding tree node by hand with a head node
 *   2. use MakeTreeByString fucntion to build a bi-tree  
 *      by a string which is in pre-order sequence 
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct treenode {
  DataType data;
  struct treenode * leftChild;
  struct treenode * rightChild;
}TreeNode;

void Initiate(TreeNode **root) {
  *root = (TreeNode *)malloc(sizeof(TreeNode));
  (*root)->leftChild = NULL;
  (*root)->rightChild = NULL;
}

/* curr指针所指结点的左孩子处插入新结点，以前的左孩子变成新节点的左孩子 */
TreeNode *InsertLeftNode(TreeNode *curr, DataType x) {
  TreeNode *s, *t;
  if (curr == NULL)  // 当前指针为空，没有指向有效结点
    return NULL;
  t = curr->leftChild;
  s = (TreeNode *)malloc(sizeof(TreeNode));
  s->data = x;
  s->leftChild = t;
  s->rightChild = NULL;
  curr->leftChild = s;
  return curr->leftChild;
}

/* curr指针所指结点的右孩子处插入新结点，以前的右孩子变成新节点的右孩子 */
TreeNode *InsertRightNode(TreeNode *curr, DataType x) {
  // 在此处添加函数代码
  TreeNode *s;
  if (curr == NULL)  // 当前指针为空，没有指向有效结点
    return NULL;
  s = (TreeNode *)malloc(sizeof(TreeNode));
  s->data = x;
  s->rightChild = curr->rightChild;
  s->leftChild = NULL;
  curr->rightChild = s;
  return curr->rightChild;
  
}

void PrintBiTree(TreeNode *bt, int n) {
  int i;
  if (bt == NULL) return;
  PrintBiTree(bt->rightChild, n+1);
  for (i = 0; i < n-1; i++) printf("   ");
  if (n > 0) {
    printf("---");
    printf("%c\n", bt->data);
  }
  PrintBiTree(bt->leftChild, n+1);
}

void MakeCharTree(TreeNode **bt) {
  
  /*
  TreeNode *p, *pp;
  Initiate(bt);
  p = InsertLeftNode(*bt, 'A');
  p = InsertLeftNode(p, 'B');
  p = InsertLeftNode(p, 'D');
  p = InsertRightNode(p, 'G');
  p = InsertRightNode((*bt)->leftChild, 'C');
  pp = p;
  InsertLeftNode(p, 'E');
  InsertRightNode(pp, 'F');
  */

  TreeNode *p, *t;
  Initiate(bt);
  
  p = InsertLeftNode(*bt, 'A');
  p = InsertLeftNode(p, 'B');
  t = p;
  p = InsertLeftNode(p, 'D');
  p = InsertRightNode(t, 'E');
  p = InsertLeftNode(p, 'H');

  p = InsertRightNode((*bt)->leftChild, 'C');
  t = p;
  p = InsertLeftNode(p, 'F');
  p = InsertRightNode(p, 'I');
  p = InsertRightNode(t, 'G');
}

void MakeCharTree2(TreeNode **bt) {
  char ch;
  ch = getchar();

  if (ch == '$') {
    *bt = NULL;
  }
  else {
    *bt = (TreeNode*)malloc(sizeof(TreeNode));
    (*bt)->data = ch;
    MakeCharTree2(&((*bt)->leftChild));
    MakeCharTree2(&((*bt)->rightChild));
  }
}

void MakeTreeByString(TreeNode **bt) {
  Initiate(bt);
  MakeCharTree2(&((*bt)->leftChild));
}

void Print(TreeNode * pNode) {
  printf("%c ", pNode->data);
}

void RecPreorder(TreeNode *t, void (*visit)(TreeNode * pNode)) {
  if (t != NULL) {
    visit(t);
    RecPreorder(t->leftChild, visit);
    RecPreorder(t->rightChild, visit);
  }
}

void RecInorder(TreeNode *t, void (*visit)(TreeNode * pNode)) {
  if (t != NULL) {
    RecInorder(t->leftChild, visit);
    visit(t);
    RecInorder(t->rightChild, visit);
  }
}

void RecPostorder(TreeNode *t, void (*visit)(TreeNode * pNode)) {
  if (t != NULL) {
    RecPostorder(t->leftChild, visit);
    RecPostorder(t->rightChild, visit);
    visit(t);
  }
}

int RecPostCalculate(TreeNode *t) {
  if (t->data >= '0' && t->data <= '9')
    return t->data - '0';
  else {
    int rst;
    switch(t->data) {
    case '+': rst = RecPostCalculate(t->leftChild) + RecPostCalculate(t->rightChild); break;
    case '-': rst = RecPostCalculate(t->leftChild) - RecPostCalculate(t->rightChild); break;
    case '*': rst = RecPostCalculate(t->leftChild) * RecPostCalculate(t->rightChild); break;
    case '/': rst = RecPostCalculate(t->leftChild) / RecPostCalculate(t->rightChild); break;
    }
    return rst;
  }
    
    
}


int count(TreeNode *r) {
  if (r == NULL) return 0;
  if (r->leftChild == NULL && r->rightChild == NULL) return 1;
  return count(r->leftChild) + count(r->rightChild);
}
int main() {
  TreeNode *root, *root2;
  //MakeCharTree(&root);
  //PrintBiTree(root->leftChild, 1);

  /*       A          */
  /*     /   \        */
  /*   B       C      */
  /*  /  \    / \     */
  /* D    E  F   G    */
  /*     /    \       */
  /*    H      I      */
  // tree pre-order sequence: pre-order:  A - B - D - E - H - C - F - I - G
  // extended pre-order: ABD$$EH$$$CF$I$$G$$
  // MakeTreeByString(&root2);
  // PrintBiTree(root2, 1);
  /*****************************************/
  /* RecPreorder(root->leftChild, Print);  */
  /* putchar('\n');			   */
  /* RecInorder(root->leftChild, Print);   */
  /* putchar('\n');			   */
  /* RecPostorder(root->leftChild, Print); */
  /* putchar('\n');			   */
  /*****************************************/

  /////////////////
  MakeTreeByString(&root2);
  PrintBiTree(root2->leftChild, 1);
  printf("%d\n", RecPostCalculate(root2->leftChild));
  printf("%d", count(root2->leftChild));
  return 0;
}

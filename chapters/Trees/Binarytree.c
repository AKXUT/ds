#include <stdio.h>
#include <stdlib.h>
typedef char DataType;
typedef struct Node {
  DataType elm;
  struct Node *left;
  struct Node *right;
} BiNode, *BiTree;

void InitTree(BiTree *ptrTree) {
  *ptrTree = malloc(sizeof(BiNode));
  (*ptrTree)->left = NULL;
  (*ptrTree)->right = NULL;
}

/*左子树插入结点*/
BiTree InsertLeftNode(BiNode *curr, DataType x) {
  BiNode *s, *t;
  if(curr == NULL) return NULL;
  t = curr->left;
  s = (BiNode *)malloc(sizeof(BiTree));
  s->elm = x;
  s->left = t;
  s->right = NULL;
  curr->left = s;
  return curr->left;	
}


/*右子树插入结点*/
BiTree InsertRightNode(BiNode *curr, DataType x) {
  BiNode *s, *t;
  if(curr == NULL) return NULL;
  t = curr->right;
  s = (BiNode *)malloc(sizeof(BiTree));
  s->elm = x;
  s->right = t;
  s->left = NULL;
  curr->right = s;
  return curr->right;	
}


/*删除子树*/
void Destroy(BiTree *root) {
  if((*root) != NULL && (*root)->left != NULL) Destroy(&(*root)->left);
  if((*root) != NULL && (*root)->right != NULL) Destroy(&(*root)->right);
  free(*root);
}


/*删除左子树*/
BiNode *DeleteLeftTree(BiNode *curr){
  if(curr == NULL || curr->left == NULL) return NULL;
  Destroy(&curr->left);
  curr->left = NULL;
  return curr;
}


int main()
{
  BiTree root, p;
  InitTree(&root);
  p = InsertLeftNode(root, 'A');
  p = InsertLeftNode(p, 'B');
  p = InsertLeftNode(p, 'D');
  p = InsertRightNode(p, 'G');
  p = InsertRightNode(root->left, 'C');
  InsertLeftNode(p, 'E');
  InsertRightNode(p, 'F');
  return 0;
}


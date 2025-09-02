#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_Q_SIZE 500

// 二叉树节点
struct node {
  int data;
  struct node* left;
  struct node* right;
};

/* 初始化队列 */
struct node** createQueue(int *front, int *rear) {
  struct node **queue =(struct node **)malloc(sizeof(struct node*)*MAX_Q_SIZE);
  *front = *rear = 0;
  return queue;
}

/* 入队 */
void enQueue(struct node **queue, int *rear, struct node *new_node) {
    queue[*rear] = new_node;
    (*rear)++;
}

/* 出队 */
struct node *deQueue(struct node **queue, int *front) {
  (*front)++;
  return queue[*front - 1];
}

/* 判断队空 */
bool isQueueEmpty(int *front, int *rear){
   return (*rear == *front);
}

/* 创建新节点 */
struct node* newNode(int data) {
   struct node* node = (struct node*)malloc(sizeof(struct node));
   node->data = data;
   node->left = NULL;
   node->right = NULL;

   return(node);
}


/* 输入二叉树树根指针，判断是否为完全二叉树 */
bool isCompleteBT(struct node* root) {
  // 空树默认是一颗完全二叉树
  if (root == NULL)  return true;

  // 创建空队列
  int rear, front;
  struct node **queue = createQueue(&front, &rear);
  // 二孩标变量志flag
  // 结点有两个孩子 flag = false
  // 否则 flag = true
  bool flag = false;
  
  // 利用队列进行层次遍历
  enQueue(queue, &rear, root);
  while(!isQueueEmpty(&front, &rear)) {
    struct node *temp_node = deQueue(queue, &front);
    if(temp_node->left)  { // 检查是否有左孩子
      if (flag == true)
	return false;
      enQueue(queue, &rear, temp_node->left); // 左孩子入队
    }
    else // 无左孩子
      flag = true;
    if(temp_node->right) { // 检查是否有右孩子
      if(flag == true)
	return false;
      enQueue(queue, &rear, temp_node->right); // 右孩子入队
    }
    else // 如果该结点不是二孩节点，则置flag为true
      flag = true;
  }
  // 如果走到这一步，那么就是一颗完全二叉树
  return true;
}

int main()
{
/* 构造如下二叉树，进行判断
                        1
                       /  \
                      2    3
                     / \    \
                    4   5    6
*/

  struct node *root = newNode(1);
  root->left        = newNode(2);
  root->right	    = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);
  root->right->right = newNode(6);
  if (isCompleteBT(root) == true)
    printf ("Yes");
  else
    printf ("NO");
  return 0;
}


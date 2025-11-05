/*************************************************
 * Created by David on Wed Nov  5 17:44:41 2025  *
 *************************************************/

#include "avl.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

/* ------------ Internal node ------------ */
struct AVLNode {
    int key;
    int height;            // 1 for leaf
    struct AVLNode *left;
    struct AVLNode *right;
};

/* ------------ Utilities ------------ */
static int max(int a, int b) { return a > b ? a : b; }
static int nheight(AVLNode *node) { return node ? node->height : 0; }

static AVLNode* make_node(int key) {
    AVLNode *new_node = (AVLNode*)malloc(sizeof(AVLNode));
    if (!new_node) abort();
    new_node->key = key;
    new_node->height = 1;
    new_node->left = new_node->right = NULL;
    return new_node;
}

static void update_height(AVLNode *node) {
    if (node)
      node->height = 1 + max(nheight(node->left), nheight(node->right));
}

static int balance_factor(AVLNode *node) {
    return node ? nheight(node->left) - nheight(node->right) : 0;
}

/* Rotations */
static AVLNode* rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y; y->left = T2;
    update_height(y); update_height(x);
    return x;
}

static AVLNode* rotate_left(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x; x->right = T2;
    update_height(x); update_height(y);
    return y;
}

static AVLNode* rebalance(AVLNode *node) {
    update_height(node);
    int bf = balance_factor(node);
    if (bf > 1) {
        if (balance_factor(node->left) < 0) node->left = rotate_left(node->left);
        return rotate_right(node);
    } else if (bf < -1) {
        if (balance_factor(node->right) > 0) node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

static AVLNode* min_node(AVLNode *node) {
    while (node && node->left) node = node->left;
    return node;
}

/* ------------ Public: lifecycle ------------ */
void avl_init(AVLTree *t) { t->root = NULL; t->size = 0; }

static void free_rec(AVLNode *n) {
    if (!n) return;
    free_rec(n->left);
    free_rec(n->right);
    free(n);
}

void avl_free(AVLTree *t) {
    free_rec(t->root);
    t->root = NULL;
    t->size = 0;
}

/* ------------ Public: core ops ------------ */
static AVLNode* insert_rec(AVLNode *root, int key, int *changed) {
    if (!root) { *changed = 1; return make_node(key); }
    if (key < root->key)       root->left  = insert_rec(root->left, key, changed);
    else if (key > root->key)  root->right = insert_rec(root->right, key, changed);
    else return root; // duplicate
    return rebalance(root);
}
int avl_insert(AVLTree *t, int key) {
    int changed = 0;
    t->root = insert_rec(t->root, key, &changed);
    if (changed) t->size++;
    return changed;
}

static AVLNode* delete_rec(AVLNode *root, int key, int *changed) {
    if (!root) return NULL;

    if (key < root->key) {
        root->left = delete_rec(root->left, key, changed);
    } else if (key > root->key) {
        root->right = delete_rec(root->right, key, changed);
    } else {
        *changed = 1;
        if (!root->left || !root->right) {
            AVLNode *tmp = root->left ? root->left : root->right;
            free(root);
            return tmp;
        } else {
            AVLNode *succ = min_node(root->right);
            root->key = succ->key;
            root->right = delete_rec(root->right, succ->key, changed);
        }
    }
    return rebalance(root);
}
int avl_delete(AVLTree *t, int key) {
    int changed = 0;
    t->root = delete_rec(t->root, key, &changed);
    if (changed) t->size--;
    return changed;
}

/* ------------ Public: queries ------------ */
int avl_contains(const AVLTree *t, int key) {
    AVLNode *n = t->root;
    while (n) {
        if (key < n->key) n = n->left;
        else if (key > n->key) n = n->right;
        else return 1;
    }
    return 0;
}
size_t avl_size(const AVLTree *t)   { return t->size; }
int     avl_height(const AVLTree *t){ return nheight(t->root); }

/* Validation helpers */
static int is_bst(AVLNode *n, int minv, int maxv) {
    if (!n) return 1;
    if (n->key <= minv || n->key >= maxv) return 0;
    return is_bst(n->left, minv, n->key) && is_bst(n->right, n->key, maxv);
}
static int is_avl(AVLNode *n) {
    if (!n) return 1;
    int bf = balance_factor(n);
    if (bf < -1 || bf > 1) return 0;
    return is_avl(n->left) && is_avl(n->right);
}
static int check_heights(AVLNode *n) {
    if (!n) return 0;
    int lh = check_heights(n->left);
    int rh = check_heights(n->right);
    if (lh < 0 || rh < 0) return INT_MIN;
    int expect = 1 + (lh > rh ? lh : rh);
    return (n->height == expect) ? expect : INT_MIN;
}
int avl_validate(const AVLTree *t) {
    AVLNode *r = t->root;
    return is_bst(r, INT_MIN, INT_MAX) && is_avl(r) && check_heights(r) >= 0;
}

/* ------------ Public: traversals ------------ */
static void inorder_rec(AVLNode *n, void (*visit)(int,int,void*), void *u) {
    if (!n) return;
    inorder_rec(n->left, visit, u);
    visit(n->key, n->height, u);
    inorder_rec(n->right, visit, u);
}
void avl_traverse_inorder(const AVLTree *t,
                          void (*visit)(int key, int height, void *user),
                          void *user) {
    inorder_rec(t->root, visit, user);
}

/* Simple queue for level-order */
typedef struct QNode { AVLNode *n; struct QNode *next; } QNode;
static void qpush(QNode **h, QNode **t, AVLNode *n) {
    QNode *q = (QNode*)malloc(sizeof(QNode));
    if (!q) abort();
    q->n = n; q->next = NULL;
    if (*t) (*t)->next = q; else *h = q;
    *t = q;
}
static AVLNode* qpop(QNode **h, QNode **t) {
    if (!*h) return NULL;
    QNode *q = *h; AVLNode *n = q->n; *h = q->next; if (!*h) *t = NULL; free(q); return n;
}

void avl_traverse_level(const AVLTree *t,
                        void (*visit)(int key, int height, void *user),
                        void *user) {
    AVLNode *r = t->root;
    if (!r) return;
    QNode *h=NULL, *tt=NULL;
    qpush(&h,&tt,r);
    while (h) {
        AVLNode *n = qpop(&h,&tt);
        visit(n->key, n->height, user);
        if (n->left)  qpush(&h,&tt,n->left);
        if (n->right) qpush(&h,&tt,n->right);
    }
}

/* internal helper: recursive right-first print */
static void print_ascii_rec(const AVLNode *n, int depth) {
  
    if (!n) return;

    // Print right subtree first (so it appears on top)
    print_ascii_rec(n->right, depth + 1);

    // Indentation
    for (int i = 0; i < depth; ++i)
        printf("    ");  // 4 spaces per level

    // Node itself
    printf("%d(h=%d)\n", n->key, n->height);

    // Then print left subtree
    print_ascii_rec(n->left, depth + 1);
}

void avl_print_ascii(const AVLTree *t) {
    if (!t || !t->root) {
        printf("(empty tree)\n");
        return;
    }
    print_ascii_rec(t->root, 0);
}

int main(void){
    AVLTree t;
    avl_init(&t);
    avl_insert(&t, 1);
    avl_insert(&t, 2);
    avl_insert(&t, 3);
    avl_insert(&t, 4);
    avl_insert(&t, 5);
    avl_insert(&t, 6);
    avl_insert(&t, 7);
    avl_insert(&t, 8);

    
    printf("size=%zu, height=%d, valid=%d\n\n",
           avl_size(&t), avl_height(&t), avl_validate(&t));

    avl_print_ascii(&t);
    
    avl_free(&t);
    return 0;
}

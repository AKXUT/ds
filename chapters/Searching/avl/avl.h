#include <stddef.h>  // size_t

/* Opaque node type */
typedef struct AVLNode AVLNode;

/* Tree handle */
typedef struct {
    AVLNode *root;
    size_t   size;
} AVLTree;

/* Lifecycle */
void avl_init(AVLTree *t);
void avl_free(AVLTree *t);  // frees all nodes, leaves t empty

/* Core ops (return 1 on change, 0 if no-op: duplicate/not-found) */
int  avl_insert(AVLTree *t, int key);
int  avl_delete(AVLTree *t, int key);

/* Queries */
int  avl_contains(const AVLTree *t, int key);  // 1 if present, else 0
size_t avl_size(const AVLTree *t);             // number of keys
int  avl_height(const AVLTree *t);             // 0 for empty, else height>=1
int  avl_validate(const AVLTree *t);           // checks BST+AVL+heights

/* Traversals (visitor gets key and node height) */
void avl_traverse_inorder(const AVLTree *t,
                          void (*visit)(int key, int height, void *user),
                          void *user);

void avl_traverse_level(const AVLTree *t,
                        void (*visit)(int key, int height, void *user),
                        void *user);

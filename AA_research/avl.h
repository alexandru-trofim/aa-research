#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node {
    int data;                                           /* Pointer to data */
    struct tree_node *parent;                             /* Pointer to parent node */
    struct tree_node *left;                               /* Pointer to left child node */
    struct tree_node *right;                              /* Pointer to right child node */
    unsigned int height;                                  /* Height of a node */
} tree_node_t;

typedef struct tree {
    tree_node_t *root;                                      /* Pointer to tree root */
    tree_node_t *nil;                                       /* Black hole pointer */
    size_t size;                                          /* Size of the avl tree */
} tree_t;

tree_t* tree_init();
tree_node_t* create_new_node(int data, tree_t *tree);
int insert_node(tree_t* tree, int data);
void print_inorder(tree_t* tree, tree_node_t* node, FILE* fd);
tree_node_t* find_node(tree_t * tree, int data);
int delete_node(tree_t * tree, int data);
int edit_elements(tree_t* tree, int value_to_edit, int new_value);
int free_tree(tree_t* tree); 

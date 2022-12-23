#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

tree_t* tree_init() {
    tree_t *new_tree = (tree_t *)malloc(sizeof(*new_tree));

    if (new_tree == NULL) {
        exit(1);
    }

    /*nil node creation*/
    new_tree->nil = (tree_node_t *)malloc(sizeof(*new_tree->nil));
    new_tree->nil->parent = new_tree->nil;
    new_tree->nil->left = new_tree->nil;
    new_tree->nil->right = new_tree->nil;
    new_tree->nil->height = 0;
    

    /*root node assign nil at beggining*/ 
    new_tree->root = new_tree->nil;

    /*set tree size*/ 
    new_tree->size = 0;

    return new_tree;
}


tree_node_t* create_new_node(int data, tree_t *tree) {
    /*new node allocation*/
    tree_node_t* new_node = (tree_node_t*)malloc(sizeof(*new_node));

    if (tree == NULL) {
        return NULL;
    }
    if (new_node == NULL) {
        return NULL;
    }

    //create default node
    new_node->data = data;
    new_node->height = 1;
    new_node->parent = new_node->left = new_node->right = tree->nil;

    return new_node;
}

int max(int a, int b) {
    return (a>=b) ? a : b;
}

void update_node_height(tree_t * tree, tree_node_t * node) {
    /* Check if input data is valid */
    if (node != tree->nil) {

        /* Update node height */
        node->height = max(node->left->height, node->right->height) + 1;
    }
}

void rotate_left(tree_t* tree, tree_node_t * node) {
    /* Check if input data is valid */
    if ((NULL == tree) || (tree->nil == node)) {
        return;
    }

    /* Check if rotation may happen */
    if (tree->nil == node->right) {
        return;
    }

    /* Set new rotated sub-root */
    tree_node_t * rotate_node = node->right;

    /* Update child of node */
    node->right = rotate_node->left;

    /* Update child parent to node */
    if (tree->nil != rotate_node->left) {
        rotate_node->left->parent = node;
    }

    /* Rotation to left */
    rotate_node->left = node;

    /* Update new sub-root parent */
    rotate_node->parent = node->parent;

    /* Update node parent to new sub-root */
    node->parent = rotate_node;

    /* Update new sub-root links to the rest of tree */
    if (tree->nil != rotate_node->parent) {
        if (rotate_node->data >= rotate_node->parent->data) {
            rotate_node->parent->right = rotate_node;
        } else {
            rotate_node->parent->left = rotate_node;
        }
    } else {
        tree->root = rotate_node;
    }

    /* Update the height of rotated avl tree node objects */
    update_node_height(tree, node);
    update_node_height(tree, rotate_node);
}

void rotate_right(tree_t * tree, tree_node_t * node) {
    /* Check if input data is valid */
    if ((NULL == tree) || (tree->nil == node)) {
        return;
    }

    /* Check if rotation may happen */
    if (tree->nil == node->left) {
        return;
    }

    /* Set new rotated sub-root */
    tree_node_t * const rotate_node = node->left;

    /* Update child of node */
    node->left = rotate_node->right;

    /* Update child parent to node */
    if (tree->nil != rotate_node->right) {
        rotate_node->right->parent = node;
    }

    /* Rotation to right */
    rotate_node->right = node;

    /* Update new sub-root parent */
    rotate_node->parent = node->parent;

    /* Update node parent to new sub-root */
    node->parent = rotate_node;

    /* Update new sub-root links to the rest of tree */
    if (tree->nil != rotate_node->parent) {
        if (rotate_node->data >= rotate_node->parent->data) {
            rotate_node->parent->right = rotate_node;
        } else {
            rotate_node->parent->left = rotate_node;
        }
    } else {
        tree->root = rotate_node;
    }

    /* Update the height of rotated avl tree node objects */
    update_node_height(tree, node);
    update_node_height(tree, rotate_node);
}


int get_node_balance(tree_node_t * node) {
    /* Return balance factor of the node */
    return (node->left->height - node->right->height);
}



int insert_fix_node_up(tree_t* tree, tree_node_t *node) {
    /* Check if input data is valid */
    if (NULL == tree) {
        return 1;
    }

    if (tree->nil == node) {
        return 1;
    }

    /* Fix avl tree */
    while (tree->nil != node) {

        /* Update height of the current node */
        update_node_height(tree, node);

        /* Get balance factors of the current node */
        int node_balance_factor = get_node_balance(node);
        int node_left_balance_factor = get_node_balance(node->left);
        int node_right_balance_factor = get_node_balance(node->right);

        /* Left-Left rotation case */
        if ((2 == node_balance_factor) && (1 == node_left_balance_factor)) {
            rotate_right(tree, node);
        }

        /* Right-Right rotation case */
        if ((-2 == node_balance_factor) && (-1 == node_right_balance_factor)) {
            rotate_left(tree, node);
        }

        /* Left-Right rotation case */
        if ((2 == node_balance_factor) && (-1 == node_left_balance_factor)) {
            rotate_left(tree, node->left);
            rotate_right(tree, node);
        }

        /* Right-Left rotation case */
        if ((-2 == node_balance_factor) && (1 == node_right_balance_factor)) {
            rotate_right(tree, node->right);
            rotate_left(tree, node);
        }

        /* Fix next node */
        node = node->parent;
    }

    /* All good */
    return 0; //don't forget to check if return is 0 in insert
}

int insert_node(tree_t* tree, int data) {
    /* Check if tree and data are valid */
    if (NULL == tree) {
        return 1;
    }

    /* Set iterator pointers */
    tree_node_t *iterator = tree->root;
    tree_node_t *parent_iterator = tree->nil;

    /* Find a valid position for insertion */
    while (tree->nil != iterator) {
        parent_iterator = iterator;

        if (iterator->data > data) {
            iterator = iterator->left;
        } else if (iterator->data < data) {
            iterator = iterator->right;
        } else {

            /*
             * Node already exists in current avl tree
             * increment count value of node
             */
            return 1;
        }
    }

    /* Create a new avl node object */
    tree_node_t *new_node = create_new_node(data, tree);

    /* Check if new avl node was created */
    if (tree->nil == new_node) {
        return 1;
    }
        
    if (tree->nil != parent_iterator) {

        /* Update parent links */
        new_node->parent = parent_iterator;

        /* Update children links */
        if (parent_iterator->data > new_node->data) {
            parent_iterator->left = new_node;
        } else {
            parent_iterator->right = new_node;
        }

        /* Fix tree is needed */
        int res = insert_fix_node_up(tree, parent_iterator);
        if (res == 1) {
        }
    } else {

        /* Created node is root node */
        tree->root = new_node;
    }

    /* Increase avl tree size */
    ++(tree->size);

    /* Insertion in avl went successfully */
    return 0;
}

void print_inorder(tree_t* tree, tree_node_t* node, FILE* fd) {
    if (node == tree->nil) {
        return;
    }
    
    /* first recur on left child */
    print_inorder(tree, node->left, fd);
 
    /* then print the data of node */
    fprintf(fd, "%d\n", node->data);
 
    /* now recur on right child */
    print_inorder(tree, node->right, fd);
}

tree_node_t* find_node(tree_t * tree, int data) {
    /* Check if input data is valid */
    if ((NULL == tree) || (tree->nil == tree->root)) {
        return tree->nil;
    }

    /* Set iterator pointer */
    tree_node_t *iterator = tree->root;

    /* Search for input data (void *data) in all tree */
    while (tree->nil != iterator) {
        if (iterator->data < data) {
            iterator = iterator->right;
        } else if (iterator->data > data) {
            iterator = iterator->left;
        } else {
            return iterator;
        }
    }

    /* Data was not found */
    return tree->nil;
}
int swap_nodes(tree_t* tree, tree_node_t* dest_node, tree_node_t* src_node) {
    /* Check if swap is posible */
    if ((tree->nil == dest_node) || (tree->nil == src_node)) {
        return 1;
    }

    /* Interchange the right child */

    tree_node_t *temp = dest_node->right;

    dest_node->right = src_node->right;

    if (tree->nil != dest_node->right) {
        dest_node->right->parent = dest_node;
    }

    src_node->right = temp;

    if (tree->nil != src_node->right) {
        src_node->right->parent = src_node;
    }

    /* Interchange the left child */

    temp = dest_node->left;

    dest_node->left = src_node->left;

    if (tree->nil != dest_node->left) {
        dest_node->left->parent = dest_node;
    }

    src_node->left = temp;

    if (tree->nil != src_node->left) {
        src_node->left->parent = src_node;
    }

    /* Interchange parents of the two nodes */

    temp = dest_node->parent;

    dest_node->parent = src_node->parent;

    if (tree->nil != dest_node->parent) {
        if (dest_node->parent->left == src_node) {
            dest_node->parent->left = dest_node;
        } else {
            dest_node->parent->right = dest_node;
        }
    } else {
        tree->root = dest_node;
    }

    src_node->parent = temp;

    if (tree->nil != src_node->parent) {
        if (src_node->parent->left == dest_node) {
            src_node->parent->left = src_node;
        } else {
            src_node->parent->right = src_node;
        }
    } else {
        tree->root = src_node;
    }

    /* All good */
    return 0;
}
tree_node_t* min_node(tree_t* tree, tree_node_t* root) {
    if (tree->nil != root) {
        while (tree->nil != root->left) {
            root = root->left;
        }
    }
    return root;
}

int delete_fix_node_up(tree_t* tree, tree_node_t* fix_node) {
    /* Check if input data is valid */
    if (NULL == tree) {
        return 1;
    }

    if (tree->nil == fix_node) {
        return 1;
    }

    /* Fix avl tree */
    while (tree->nil != fix_node) {

        /* Update height of the current node */
        update_node_height(tree, fix_node);

        /* Get balance factors of the current node */
        int node_balance_factor = get_node_balance(fix_node);
        int node_left_balance_factor = get_node_balance(fix_node->left);
        int node_right_balance_factor = get_node_balance(fix_node->right);

        /* Left-Left rotation case */
        if ((node_balance_factor > 1) && (node_left_balance_factor >= 0)) {
            rotate_right(tree, fix_node);
        }

        /* Right-Right rotation case */
        if ((node_balance_factor < -1) && (node_right_balance_factor <= 0)) {
            rotate_left(tree, fix_node);
        }

        /* Left-Right rotation case */
        if ((node_balance_factor > 1) && (node_left_balance_factor < 0)) {
            rotate_left(tree, fix_node->left);
            rotate_right(tree, fix_node);
        }

        /* Right-Left rotation case */
        if ((node_balance_factor < -1) && (node_right_balance_factor > 0)) {
            rotate_right(tree, fix_node->right);
            rotate_left(tree, fix_node);
        }

        /* Fix next node */
        fix_node = fix_node->parent;
    }

    return 0;
}



int delete_node(tree_t * tree, int data) {
    /* Check if input data is valid */
    if (NULL == tree) {
        return 1;
    }

    if (tree->nil == tree->root) {
        return 1;
    }

    /* Find current node (root) in avl tree */
    tree_node_t *delete_node = find_node(tree, data);

    /* Bst node was not found exit process */
    if (tree->nil == delete_node) {
        return 1;
    }

    /* Delete selected node */
    if ((tree->nil != delete_node->left) && (tree->nil != delete_node->right)) {

        /* Selected node has two children */

        /* Find a replacement for selected node */
        tree_node_t *delete_successor = min_node(tree, delete_node->right);
                
        /* Replace the selected avl node and remove the dublicate */
        int err = swap_nodes(tree, delete_node, delete_successor);

        if (0 != err) {
            return err;
        }
    }

    /* Selected node has one or no chlid */

    if (tree->nil != delete_node->left) {

        /* Selected node has a left child */

        /* Update child-grandparent links */
        delete_node->left->parent = delete_node->parent;

        if (tree->nil != delete_node->parent) {

            /* Update grandparent-child links */

            if (delete_node->parent->right == delete_node) {
                delete_node->parent->right = delete_node->left;
            } else {
                delete_node->parent->left = delete_node->left;
            }
        } else {

            /*
                * Selected node was root
                * Update a new root
                */
            tree->root = delete_node->left;
        }
    } else if (tree->nil != delete_node->right) {

        /* Selected node has a right child */

        /* Update child-grandparent links */
        delete_node->right->parent = delete_node->parent;

        if (tree->nil != delete_node->parent) {

            /* Update grandparent-child links */

            if (delete_node->parent->right == delete_node) {
                delete_node->parent->right = delete_node->right;
            } else {
                delete_node->parent->left = delete_node->right;
            }
        } else {

            /*
                * Selected node was root
                * Update a new root
                */
            tree->root = delete_node->right;
        }
    } else {

        /* Selected node has no children */

        /* Update grandparent links */
        if (tree->nil != delete_node->parent) {
            if (delete_node->parent->right == delete_node) {
                delete_node->parent->right = tree->nil;
            } else {
                delete_node->parent->left = tree->nil;
            }
        } else {

            /*
                * Selected node was root
                * Update new root to NULL
                */
            tree->root = tree->nil;
        }
    }

    tree_node_t *parent_delete_node = delete_node->parent;


    /* Free selected avl node pointer */
    if (tree->nil != delete_node) {
        free(delete_node);
    }

    /* Set selected avl node as NULL */
    delete_node = tree->nil;

    /* Deacrease tree size  */
    --(tree->size);
    
    /* Fix avl tree if needed */
    if (tree->nil == parent_delete_node) {
        return 0;
    }

    return delete_fix_node_up(tree, parent_delete_node);
}


int edit_elements(tree_t* tree, int value_to_edit, int new_value) {
    tree_node_t* node_found = find_node(tree, value_to_edit);

    if (node_found == tree->nil) {
        return 1;
    }

    /*Node we want to edit is deleted*/
    delete_node(tree, node_found->data);

    /*Now we create a new node with new data*/
    insert_node(tree, new_value);

    return 0;
}

void free_tree_helper(tree_t* tree, tree_node_t ** root) {
    /* Check if current node is valid */
    if (tree->nil == *root) {
        return;
    }

    /* Recursive calls */
    free_tree_helper(tree, &(*root)->left);
    free_tree_helper(tree, &(*root)->right);


    /* Free avl node pointer */
    if (tree->nil != *root) {
        free(*root);

        *root = tree->nil;
    }
}

int free_tree(tree_t* tree) {
    /* Check if tree needs to be freed */
    if (NULL != tree) {

        /* Free every node from avl -> tree */
        free_tree_helper(tree, &tree->root);
        
        /* Free `nil` cell*/
        free(tree->nil);

        tree->nil = NULL;        

        /* Free avl tree object */
        free(tree);

        return 0;
    }

    return 1;
}

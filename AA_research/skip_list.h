#include <stdlib.h>
#include <stdio.h>


typedef struct snode {
    int key;
    struct snode **forward;
} snode;

typedef struct skiplist {
    int level;
    struct snode *header;
} skiplist;


skiplist *skiplist_init();
int skiplist_insert(skiplist *list, int key);
snode *skiplist_search(skiplist *list, int key);
int skiplist_delete(skiplist *list, int key);
int skiplist_edit(skiplist* list, int val_to_edit, int new_val);
void skiplist_free(skiplist *list);
void skiplist_dump(skiplist *list, int layer, FILE* fd);
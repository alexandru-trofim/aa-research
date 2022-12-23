#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "avl.h"

#define NR_OF_TESTS 21

int main(int argc, char* argv[]) {

    

    for(int i = 1; i <= NR_OF_TESTS; ++i) {
        tree_t *tree = tree_init();
        char test_nr[5];
        char in_file[20];
        char out_file[20];
        int command = 0, value = 0, value2 = 0, N = 0;
        sprintf(test_nr, "%d", i);

        strcpy(in_file, "in/test");
        strcat(in_file, test_nr);
        strcat(in_file, ".in");

        strcpy(out_file, "out/test");
        strcat(out_file, test_nr);
        strcat(out_file, ".out");

        FILE* in = fopen(in_file,"r");
        FILE* out= fopen(out_file,"w");
        fscanf(in,"%d", &N);
        for(int i = 0; i < N; ++i) {

            fscanf(in, "%d", &command);
            switch (command)
            {
            case 0: {
                fscanf(in, "%d", &value);
                insert_node(tree, value);
                break;
            }
            case 1: {
                fscanf(in, "%d", &value);
                delete_node(tree, value);
                break;
            }
            case 2: {
                fscanf(in, "%d", &value);
                tree_node_t* res = find_node(tree, value);
                if (res == NULL) {
                    fprintf(out, "0");
                } else {
                    fprintf(out, "1");
                }
                break;
            }
            case 3: {
                fscanf(in, "%d %d", &value, &value2);
                edit_elements(tree, value, value2);
                break;
            }
            case 4: {
                print_inorder(tree, tree->root, out);
                break;
            } 
            default:
                break;
            }
        }
        free_tree(tree);

        fclose(in);
        fclose(out);

    }

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "skip_list.h"

#define NR_OF_TESTS 21 

int main(int argc, char* argv[]) {


    for(int i = 1; i <= NR_OF_TESTS; ++i) {
        skiplist* list = skiplist_init();
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
                skiplist_insert(list, value);
                break;
            }
            case 1: {
                fscanf(in, "%d", &value);
                skiplist_delete(list, value);
                break;
            }
            case 2: {
                fscanf(in, "%d", &value);
                snode* res = skiplist_search(list, value);
                if (res == NULL) {
                    fprintf(out, "0\n");
                } else {
                    fprintf(out, "1\n");
                }
                break;
            }
            case 3: {
                fscanf(in, "%d %d", &value, &value2);
                skiplist_edit(list, value, value2);
                break;
            }
            case 4: {
                skiplist_dump(list, 0, out);
                break;
            } 
            default:
                break;
            }
        }
        fclose(in);
        fclose(out);
        skiplist_free(list);
    }

    return 0;
}
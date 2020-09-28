
#include "group.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define IS_POSITIVE(X) ((X) > 0.00001)



/*arr is pre-allocated*/
void FromGroupToNArray(group* g,int* arr)
{
    int i,*arr_g;
    arr_g = g->grp;
    for(i = 0; i<g->size ;i++){
        arr[arr_g[i]] = 1;
    }
}

void freeGroup(group *g){
    free(g->grp);
    free(g);
}

void initialise_group(group *g){
    g->size = 0;
    g->grp = (int*)NULL;

}

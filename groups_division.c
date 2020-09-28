
#include "groups_division.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ERROR.h"

/*pop the first group of groups_division*/
void popFirst(groups_division *L1,group *g){
    int i;
    group *temp = L1->head;
    g->size = (temp)->size;
    for(i=0;i<g->size;i++){
        g->grp[i] = (temp)->grp[i];
    }
    L1->head = temp->next;
    freeGroup(temp);
    L1->size--;
}

void addFirst(groups_division *L1,group *g){
    int i;
    group *new_g = malloc(sizeof(group));
    if(new_g==NULL) ERROR(ALLOC)

    new_g->size = g->size;
    new_g->grp = malloc(sizeof(int)*g->size);
    if(new_g->grp == NULL) ERROR(ALLOC)

    /*copy g->grp to new_g->grp*/
    for(i=0;i<g->size;i++){
        new_g->grp[i] = g->grp[i];
    }
    new_g->next = L1->head;
    L1->head = new_g;
    L1->size++;
}



void freeGroupsDivision(groups_division* D1){
    group* temp,*curr;
    if(D1 == NULL) return;
    curr = D1->head;
    while(curr!=NULL){
        temp = curr->next ;
        freeGroup(curr);
        curr = temp;
    }
    free(D1);
}

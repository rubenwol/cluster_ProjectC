#include "spmat.h"
#include "ERROR.h"
#include <stdlib.h>
#include <stdio.h>

void add_row_list(struct _spmat *, const double *, int);
void free_list(struct _spmat *A);
void mult_list(const struct _spmat *A, const double *v, double *result);

/* Allocates a new linked-lists sparse matrix of size n */
spmat* spmat_allocate_list(int n){
    spmat *spmat1;
    spmat1 = malloc(sizeof(spmat));
    if(spmat1==NULL)ERROR(ALLOC)

    spmat1->n = n;
    spmat1->add_row = add_row_list;
    spmat1->free = free_list;
    spmat1->mult = mult_list;
    spmat1->private =(elem*)malloc(sizeof(elem*) * n);
    if(spmat1->private==NULL) ERROR(ALLOC)

    return spmat1;
}

/* Adds row i the matrix. Called before any other call,
	 * exactly n times in order (i = 0 to n-1) */
void add_row_list(struct _spmat *A, const double *row, int i) {
    int k;
    sp_linked sp_linked1 = (sp_linked) (A->private);
    elem *curr,*next_elem;
    /* initialise a pre-"headelem"*/
    elem *head = (elem*)malloc(sizeof(elem));
    if(head==NULL)ERROR(ALLOC)
    curr = head;

    /* add element in rows */
    for(k=0;k< A->n;k++) {
        if (row[k] != 0) {
            curr->next = (elem*)malloc(sizeof(elem));
            next_elem = curr->next;
            if(next_elem==NULL)ERROR(ALLOC)

            next_elem->value = row[k];
            next_elem->columnIndex = k;
            curr = next_elem;
        }
    }
    curr->next = NULL;
    sp_linked1[i] = head->next;
    free(head);
}

void free_list(struct _spmat *A) {
    int i;
    elem *curr ,*next;
    sp_linked sp_linked1 = (sp_linked) (A->private);
    for(i=0;i<(A->n); i++) {
        curr = sp_linked1[i];
        while (curr != NULL) {
            next = curr->next;
            free(curr);
            curr = next;}
    }
    free(A->private);
    free(A);
}

void mult_list(const struct _spmat *A, const double *v, double *result){
    sp_linked row = (sp_linked )(A->private);
    elem *curr;
    int i;
    for(i=0 ; i<(A->n);i++){
        /*multiply the row i with the vector*/
        curr = row[i];
        result[i] = 0;
        while(curr!=NULL){
            result[i] += (curr->value)*v[curr->columnIndex];
            curr = curr->next;
        }
    }
}


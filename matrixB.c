#include "matrixB.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ERROR.h"


double maxArray(double* arr, int n){
    int i;
    double max = arr[0];
    for(i=0;i<n;i++){
        if(arr[i]>max)
            max = arr[i];
    }
    return max;
}

/*it was mult_Bhat vector of size n*/
void mult_matK(Bhat* B,double* vec,double *res,group *g){
    double sum = 0;
    int i;
    int *grp = g->grp;
    /*calculate sum*/
    for(i=0;i<g->size;i++){
        sum+=((B->k)[grp[i]])*vec[i];
    }
    /*calculate mult*/
    for(i=0;i<g->size;i++){
        res[i] = (1.0/((double)B->M))*((B->k)[grp[i]])*sum;
    }
}

/*v is of "dimension" n and result is of dimension n */
void mult_sparse_hat(spmat* A, const double *v, double *result,group *g,int* indexg,int* arr){
    sp_linked row = (sp_linked )(A->private);
    elem *curr;
    int i;
    for(i=0;i<g->size;i++){
        /*multiply the row i with the vector*/
        curr = row[g->grp[i]];
        result[i] = 0;
        while(curr != NULL){
            if(arr[curr->columnIndex]==1){
                result[i] += (curr->value)*v[indexg[curr->columnIndex]];
            }
            curr = curr->next;
        }
    }
}
/*vec dim ng, f dim ng*/
void mult_mat_diag(double* diag,double* vec,double* res,group *g){
    int i;
    for(i=0;i<g->size;i++){
        res[i] = diag[i]*vec[i];
    }
}

void buildf(Bhat* B,double* f,group *g){
    double sum = 0.0;
    int i;
    int* grp = g->grp;
    sp_linked row = (sp_linked) ((B->A)->private);
    elem *curr;
    int *arr = calloc((B->n),sizeof(int));
    if(arr==NULL)ERROR(ALLOC)

    FromGroupToNArray(g,arr);
    for(i=0;i<g->size;i++){
        sum+=((B->k)[grp[i]]);
    }
    sum = (1.0/((double)B->M))*sum;
    for(i=0;i<g->size;i++){
        f[i]=0;
        f[i]-=sum*(B->k)[grp[i]];
    }
    for(i=0;i<g->size;i++){
        curr = row[grp[i]];
        while(curr!=NULL){
            f[i] += (curr->value)*arr[curr->columnIndex];
            curr = curr->next;
        }
    }
    free(arr);
}


double matShiftB(Bhat *B){
    double* norm1;
    double res;
    spmat* A = B->A;
    sp_linked sp_linked1 = (sp_linked) (A->private);
    elem *curr;
    int i;
    norm1 = calloc(B->n, sizeof(double));
    if(norm1==NULL) ERROR(ALLOC)

    for(i = 0 ; i < B->n;i++){
        norm1[i] = (B->k)[i];
    }
    for(i=0;i<B->n;i++) {
        curr = sp_linked1[i];
        while (curr != NULL) {
            norm1[curr->columnIndex] = norm1[curr->columnIndex] - (((B->k)[i]*(B->k)[curr->columnIndex])/((double)B->M)) + fabs(curr->value-(((B->k)[i]*(B->k)[curr->columnIndex])/((double)B->M)));
            curr = curr->next;
        }
    }
    res =  maxArray(norm1,B->n);
    free(norm1);
    return res;
}

void multBhat(Bhat* B,double *v, double *result,group *g, double* f,int *indexg,int* arr){
    double *va,*vf,*vk;
    va = calloc(g->size,sizeof(double));
    vf = calloc(g->size,sizeof(double));
    vk = calloc(g->size,sizeof(double));
    if(va==NULL || vf==NULL || vk==NULL) ERROR(ALLOC)

    mult_matK(B,v,vk,g);
    mult_mat_diag(f,v,vf,g);
    mult_sparse_hat(B->A,v,va,g,indexg,arr);

    subtractVector(va,vk,result,g->size);
    subtractVector(result,vf,result,g->size);
    free(va);
    free(vf);
    free(vk);
}


Bhat* fromFileToB(char* infile){
    int *index;
    double *rows;
    int p,i,n,j,l;
    FILE* file;
    Bhat *B;
    l = 0;

    file = fopen(infile,"r");
    if(file==NULL) ERROR(FILE_OPEN)

    p = fread(&n,sizeof(int),1,file);
    if(p!=1) ERROR(FILE_READ)

    if(n==0)ERROR(ZERO_VERTEX)

    B = malloc(sizeof(Bhat));
    if(B==NULL) ERROR(ALLOC)

    B->A = spmat_allocate_list(n);
    B->n = n;
    B->k = malloc(sizeof(int)*n);
    rows = calloc(n,sizeof(double));
    if(B->k==NULL ||rows ==NULL) ERROR(ALLOC)

    for(i=0; i<n ;i++){
        p = fread(&(B->k[i]), sizeof(int),1,file);
        if(p!=1)ERROR(FILE_READ)

        index = malloc(sizeof(int)*(B->k[i]));
        if(index==NULL)ERROR(ALLOC)

        p = fread(index, sizeof(int),(B->k[i]),file);
        if(p!=(B->k[i])) ERROR(ALLOC)

        for(j=0;j< n;j++){
            if((l < B->k[i])){
                if(j == index[l]){
                    rows[j] = 1.0;
                    l++;}
                else rows[j] = 0.0;
            }else rows[j] = 0.0;
        }
        l=0;
        (B->A)->add_row(B->A,rows,i);
        free(index);
    }
    /*calculate M*/
    B->M = 0;
    for(i=0;i<n;i++){
        B->M+=B->k[i];
    }
    if(B->M == 0) ERROR(ZERO_EDGES)

    B->shift = matShiftB(B);
    free(rows);
    fclose(file);
    return B;
}

#include "maximization.h"
#include "ERROR.h"
#include <stdlib.h>
#define IS_POSITIVE(X) ((X) > 0.00001)

void initialise_unmoved(int* unmoved,int n){
   int i;
   for(i=0;i<n;i++){
       unmoved[i] = i;
   }
}
int argmax(double* arr,int n){
    int i,argmax=0;
    double max = arr[0];
    for(i=0;i<n;i++){
        if(arr[i]>=max){
            argmax = i;
            max = arr[i];
        }
    }
    return argmax;
}

int argmax_unmoved(double *score,int* Unmoved,int n)
{
    int i,argmax = 0;
    double max;
    int is_first = 1;

    for(i = 0; i<n ; i++){
        if(Unmoved[i]==-1){
            continue;
        }else if(is_first){
            argmax = i;
            max = score[i];
            is_first = 0;
        } else if (score[i] > max){
            argmax = i;
            max = score[i];
        }
    }
    return argmax;
}

/*need to change*/
double B_i_j(Bhat *B,int i,int j, group* g){
    double res = 0;
    elem *elem;
    int* grp = g->grp;
    sp_linked row = (B->A)->private;
    res -= ((B->k[grp[i]])*(B->k[grp[j]]))/((double)B->M);

    elem = row[grp[i]];
    while(elem!=NULL){
        if(elem->columnIndex>grp[j]) break;
        if(elem->columnIndex == grp[j]){
            res+=elem->value;
            break;
        }
        elem = elem->next;
    }
    return res;
}

void algo4(Bhat *B, double *s, group *g,int *indexg,int *arr) {
    int *unmoved;
    int i,j,k,i_tag,*indices,*grp;
    double delta_Q, *x,*score,*improve,*zeros;

    score = calloc(g->size, sizeof(double));
    improve = calloc(g->size, sizeof(double));
    indices = calloc(g->size, sizeof(double));
    unmoved = calloc(g->size, sizeof(int));
    x = calloc(g->size, sizeof(double));
    zeros = calloc(g->size, sizeof(double));
    grp = g->grp;
    if(zeros ==NULL ||score ==NULL||improve == NULL||indices==NULL||unmoved==NULL||x ==NULL) ERROR(ALLOC)

    do {
        initialise_unmoved(unmoved, g->size);
        multBhat(B, s, x, g, zeros, indexg ,arr);
        for(i=0;i<g->size;i++){
            score[i] = (-2) * (s[i] * x[i] +(((B->k)[grp[i]]) * ((B->k)[grp[i]])) / ((double) (B->M)));
        }
        for(i=0; i < g->size ;i++){
            j = argmax_unmoved(score, unmoved,g->size);
            s[j] = -s[j];
            indices[i] = j;
            if (i == 0){
                improve[i] = score[j];
            }else {
                improve[i] = improve[i - 1] + score[j];
            }
            unmoved[j] = -1;

            for(k = 0 ; k < g->size ;k++){
                if (k == j) {
                    score[k] *= (-1);
                }else{
                    score[k] -= 4 * s[k] * s[j] * B_i_j(B, k, j, g);
                }
            }
        }
        i_tag = argmax(improve, g->size);
        for(i= g->size - 1; i > i_tag;i--){
                j = indices[i];
                s[j] *= (-1);
            }
        if(i_tag == g->size - 1) {
            delta_Q = 0;
        }else {
            delta_Q = improve[i_tag];
        }

    }while(IS_POSITIVE(delta_Q));

    free(score);
    free(improve);
    free(unmoved);
    free(indices);
    free(x);
    free(zeros);
}

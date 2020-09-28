#include<stdlib.h>
#include "powerIteration.h"
#include "ERROR.h"
#include <stdio.h>

void powerIteration(Bhat *B, group *g, double *f, double *newVec,int* indexg,int* arr) {
    double *vec,*vecShift,norm;
    int i,count = 0;

    /*initialise vec shift*/
    vecShift = (double*)malloc((g->size)*sizeof(double));
    vec = (double*) malloc((g->size)*sizeof(double));
    if(vec==NULL)ERROR(ALLOC)
    for(i=0;i<g->size;i++)
        vecShift[i] = f[i] - B->shift;

    /*initialise Vec*/
    /*intialise random vector*/
    for(i=0;i<g->size;i++){
        vec[i] = rand();
    }
    /*initialise newVec*/

    for(i=0;i<g->size;i++){
        newVec[i] = vec[i]+1;
    }

    while(diffIsSmaller(vec, newVec, g->size) == 0) {
        for(i=0;i<g->size;i++){
            vec[i] = newVec[i];
        }
        multBhat(B, vec, newVec, g, vecShift, indexg, arr);
        /*normalize the newVec*/
        norm = norm2(newVec, g->size);

        for(i=0;i<g->size;i++){
            newVec[i] = newVec[i] / norm;
        }
        count ++;
        if(count>=(g->size)*140000) ERROR(INFINITE_LOOP)
    }
    free(vecShift);
    free(vec);
}

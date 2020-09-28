#include "modularity.h"
#include "ERROR.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define IS_POSITIVE(X) ((X) > 0.00001)

void divideInTwo(double *closevector,group *g, group* g1,group *g2)
{
    int i=0;
    int indexg1 = 0,indexg2 = 0;

    /*initialise g1 and g2*/
    initialise_group(g1);
    initialise_group(g2);

    /*count -1 and count +1*/
    for(i = 0; i < g->size ;i++) {
        if (closevector[i] == 1)
            g1->size++;
        else
            g2->size++;
    }
    /*initialise int* grp of g1 and g2*/
    g1->grp =(int*) malloc(sizeof(int)*g1->size);
    g2->grp =(int*) malloc(sizeof(int)*g2->size);
    if(g1->grp ==NULL || g2->grp ==NULL) ERROR(ALLOC)

    for(i = 0 ;i < g->size ;i++) {
        if (closevector[i] == 1){
            g1->grp[indexg1] = g->grp[i];
            indexg1++;
        }
        else{
            g2->grp[indexg2] = g->grp[i];
            indexg2++;
        }
    }
}

double leadingEigenValue(Bhat *B,double* eigenVector,group *g,double* f,int *indexg,int *arr){
    double* B_mult_eig;
    double nominator;
    double denominator;
    B_mult_eig = calloc(g->size,sizeof(double));
    if(B_mult_eig==NULL) ERROR(ALLOC)

    multBhat(B,eigenVector,B_mult_eig,g,f,indexg,arr);
    nominator = dotProduct(eigenVector,B_mult_eig,g->size);
    denominator = dotProduct(eigenVector,eigenVector,g->size);
    free(B_mult_eig);
    if(denominator == 0) ERROR(DIVISION_BY_ZERO)
    return nominator/denominator;
}

void closeVector(double* vec,double* closevec,int n){
    int i;
    for(i =0 ; i < n;i++)
    {
        if (IS_POSITIVE(vec[i]) == 1)
            closevec[i] = 1;
        else
            closevec[i] = -1;
    }
}

void algo2(Bhat *B,group* g ,group *g1,group *g2){
    double *f,*eigenVector,*ones,*closevec;
    double leadingEigen;
    int i,*indexg,*arr;
    double sBs;
    double *Bs;
    closevec = (double*)malloc((g->size)* sizeof(double));
    indexg =  calloc((B->n), sizeof(int));
    arr =  calloc((B->n), sizeof(int));
    eigenVector = calloc((g->size), sizeof(double));
    f = calloc((g->size),sizeof(double));
    Bs = calloc((g->size),sizeof(double));
    ones = calloc((g->size),sizeof(double));
    if(closevec==NULL ||indexg==NULL||arr == NULL||eigenVector==NULL || f==NULL ||Bs ==NULL||ones==NULL) ERROR(ALLOC)

    buildf(B,f,g);
    FromGroupToNArray(g,arr);

    /*initialise vector of ones if the groupe is indivisible*/
    for(i = 0; i < (g->size); i++) {
        ones[i] = 1;
    }

    /*array of index indexg[i] = j if i is the jth number of g*/
    for(i=0;i<g->size;i++){
        indexg[g->grp[i]] = i;
    }

    powerIteration(B, g, f, eigenVector,indexg,arr);
    leadingEigen = leadingEigenValue(B,eigenVector,g,f,indexg,arr);
    multBhat(B,eigenVector,Bs,g,f,indexg,arr);
    sBs = dotProduct(eigenVector,Bs,g->size);


    if(IS_POSITIVE(leadingEigen)==0){
        free(closevec);
        free(eigenVector);
        free(f);
        free(indexg);
        free(arr);
        free(Bs);
        divideInTwo(ones,g,g1,g2);
        free(ones);
        return;
    }


    if(IS_POSITIVE(sBs)==0){
        free(closevec);
        free(eigenVector);
        algo4(B, ones, g,indexg,arr);
        free(f);
        free(indexg);
        free(arr);
        free(Bs);
        divideInTwo(ones, g, g1 ,g2);
        free(closevec);
        return;
    }
    closeVector(eigenVector,closevec,g->size);
    algo4(B, closevec, g, indexg , arr);
    free(indexg);
    free(arr);
    free(ones);
    free(eigenVector);
    free(f);
    free(Bs);
    divideInTwo(closevec,g,g1,g2);
    free(closevec);
    return;

}


/*algo 3*/
groups_division* modularity_division(char* infile,groups_division* O){
    groups_division *P;
    group *g,*g1,*g2;
    Bhat *B;
    int i;
    B = fromFileToB(infile);
    P = malloc(sizeof(groups_division));
    g = malloc(sizeof(group));
    g1 = malloc(sizeof(group));
    g2 = malloc(sizeof(group));


    if(P==NULL || g==NULL || g1 ==NULL|| g2==NULL) ERROR(ALLOC)

    /*initialize g*/
    initialise_group(g);
    g->grp = (int*)malloc(sizeof(int)*(B->n));
    if(g->grp==NULL) ERROR(ALLOC)

    g->size = (B->n);
    for(i=0; i < B->n ;i++){
        g->grp[i] = i;
    }
    /*initialise g1 and g2*/
    initialise_group(g1);
    initialise_group(g2);

    /*initialise O*/
    O->head = NULL;
    O->size = 0;
    /*initialise P*/
    P->head = NULL;
    O->size = 0;
    addFirst(P,g);
    /*implement allocation of P and O*/
    while(P->head!=NULL){
        /*initialise g1 and g2*/
        initialise_group(g1);
        initialise_group(g2);


        popFirst(P,g);
        algo2(B, g, g1, g2);
        if(g1->size == 0){
            addFirst(O,g2);
            free(g1->grp);
            free(g2->grp);
            continue;
        }
        if(g2->size == 0){
            addFirst(O,g1);
            free(g1->grp);
            free(g2->grp);
            continue;
        }
        if(g1->size == 1){
            addFirst(O,g1);
        }
        if(g2->size == 1 ){
            addFirst(O,g2);
        }
        else{
            if(g1->size != 1)
                addFirst(P,g1);
            if(g2->size != 1)
                addFirst(P,g2);

        }
        free(g1->grp);
        free(g2->grp);
    }
    freeGroupsDivision(P);
    /*need to do a function free linklist , free double link list*/
    freeGroup(g);
    free(g1);
    free(g2);
    (B->A)->free(B->A);
    free(B->k);
    free(B);
    return O;
}


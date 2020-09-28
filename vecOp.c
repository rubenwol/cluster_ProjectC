#include "vecOp.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


double dotProduct(double *v1, double *v2, int n){
    double result = 0 ;
    int i;
    for(i = 0 ; i<n ; i++){
        result+= v1[i]*v2[i];
    }
    return result;
}

double norm2(double* vector, int size){
    int i;
    double sum = 0;
    for(i = 0; i < size; i++){
        sum += vector[i]*vector[i];
    }
    return sqrt(sum) ;
}

/*size of v1 = size of v2*/
void subtractVector(double* v1,double* v2,double* res,int size){
    int i;
    for(i = 0; i < size ; i++){
        res[i] = v1[i]-v2[i];
    }
}

/*difference of the vectors smaller than epsilon*/
int diffIsSmaller(double* v1, double* v2,int n){
    int i;
    for(i = 0;i < n ; i++){
        if(fabs(v1[i]-v2[i]) >= 0.00001){
            return 0;
        }
    }
    return 1;
}

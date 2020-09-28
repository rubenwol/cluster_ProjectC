#include "spmat.h"
#include "vecOp.h"
#ifndef CLUSTERS_MATRIXB_H
#define CLUSTERS_MATRIXB_H

/**
 * the strcut matBhat containes:size,spmat A,the array k represents the degrees in the graph,M the sum of k ,shift-the norm1 of B.
 * multBhat              -Multiplies matrix B by vector v, into result (result is pre-allocated)
 * buildf               -create an array of size ng : f[i] = sum of rows of Bhat-g.
 * fromFileToB          -returns new B Matrix from given file.
 * matShiftB            -returns the desired shift-the norm1 of B.
 * double maxArray       -return max{arr[i]}
 * mult_matK             -calculate the multiplication between the matrix Kg and vector
 * mult_sparse_hat       - calculate multiplication of A_g and vector
 *mult_mat_diag          - calculate the multiplication between diagonal matrix and vector
 * matShiftB              -calculate the shift of the matrix B
 *
 */

typedef struct _matBhat{
    /* Matrix size of B (n*n) */
    int	n;
    spmat* A;
    /*array of vertex degree, k[i] = degree of vertice i*/
    int *k;
    /*M = sum(k)*/
    int M;
    /*shift = norm l1 of B*/
    double shift;

}Bhat;

/* Multiplies matrix B by vector v, into result (result is pre-allocated) */
void multBhat(Bhat *B, double *v, double *result,group* g,double* f,int* indexg,int* arr);
void buildf(Bhat* B,double* f,group *g);
Bhat* fromFileToB(char* infile);
double matShiftB(Bhat *B);
void mult_mat_diag(double* diag,double* vec,double* res,group* g);
#endif /*CLUSTERS_MATRIXB_H*/

#include "groups_division.h"
#ifndef CLUSTERS_VECOP_H
#define CLUSTERS_VECOP_H

/**
 * it is the file of vector operations:
 * dotProduct       -returns dot product of 2 given vectors of size n
 * norm2             -return the norm2 of given vector of size n
 * diffIsSmaller      -returns 1 if norm2 of v1 -v2 is zero
 * subtractVector     -subtracts v2 from v1
 *
 */

double dotProduct(double *v1, double *v2, int n);
double norm2(double* vector, int size);
/*size of v1 = size of v2*/
void subtractVector(double* v1,double* v2,double* res,int size);
int diffIsSmaller(double* v1, double* v2,int n);
#endif /*CLUSTERS_VECOP_H*/

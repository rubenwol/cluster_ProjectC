#include "vecOp.h"
#include "matrixB.h"
#ifndef CLUSTERS_POWERITERATION_H
#define CLUSTERS_POWERITERATION_H

/*powerIteration-         calculate the eigenVector of Bhat_g in newVec*/

void powerIteration(Bhat *B, group *g, double *f, double *newVec,int* indexg ,int* arr);
#endif /*CLUSTERS_POWERITERATION_H*/

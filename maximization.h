#include "matrixB.h"
#ifndef CLUSTERS_MAXIMIZATION_H
#define CLUSTERS_MAXIMIZATION_H
/*algo4                     -implementation of algo 4
 * initialise_unmoved       - Initialize unmoved array.
 *  argmax                  - Return argMax{arr[j]: j}
 *  argmax_unmoved          - Return argMax{arr[j]: s.t unmoved[j]!=-1}
 *  B_i_j                   - Return the elment Bg[i][j]
 * */
void algo4(Bhat *B, double *s, group *g,int *indexg,int *arr);
#endif /*CLUSTERS_MAXIMIZATION_H*/

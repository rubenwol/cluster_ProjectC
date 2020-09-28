#include "powerIteration.h"
#include "matrixB.h"
#include "maximization.h"

#ifndef CLUSTERS_MODULARITY_H
#define CLUSTERS_MODULARITY_H
/**
 * closeVector                   -puts 1 in indexes in which vec is greater than 0 else -1 .we do it only in indexes represented by g.
 * divideInTwo                  -given group represented by g returns 2 groups by the values of the close vector.
 * modularity_division          -returns the modularity groups by the graph of the file.
 * algo2                        -returns division of the group g to two groups.
 * leadingEigenValue            - return the leading eigen Value of Bhat
 *
 *
 */
void closeVector(double* vec,double* closevec,int n);

void divideInTwo(double *closevector,group *g, group* g1,group *g2);
/*algo 3*/
groups_division* modularity_division(char* infile,groups_division* O);


/*int* algo4(int **A,int *s1,linklist *g,int n);*/

void algo2(Bhat *B,group* g ,group *g1,group *g2);
#endif /* CLUSTERS_MODULARITY_H */

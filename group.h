#ifndef CLUSTERS_GROUP_H
#define CLUSTERS_GROUP_H


/**
 *Structure group  -each group is a node of the groups_division
 * each group contains an array "grp" that contains the nodes of the group and its size
 * next is the next group in the groups_division
 *
 * FromGroupToNArray        -create an array of dimension N (number of vertex in the graph) :arr[i]=1 if i in group ,else arr[i] = 0
 * freeGroup                -free the group g
 *initialise_group          -initialise the group g, size = 0  and pgr = NULL
 */


typedef struct group
{
    int *grp;
    int size;
    struct group *next;
}group;


void FromGroupToNArray(group* g,int* arr);
void freeGroup(group *g);
void initialise_group(group *g);
#endif /*CLUSTERS_GROUP_H*/

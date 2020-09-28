#include "group.h"
#ifndef CLUSTERS_groups_division_H
#define CLUSTERS_groups_division_H

/**
 * A groups_division such that every node points to a linkedList.
 * Every groups_division has node head.every node has 2 pointers:to the next Node(or NULL) and to his LinkedList
 * popFirst-                 -deletes the head group of the division and record her into g.
 * addFirst-                 -adds new Head instead of the previous head.the old head becomes the new's head next.
 * freeGroupsDivision        -free the group_division g
 * initialise_group
 */

typedef struct groups_division{
    group *head;
    int size;
}groups_division;

void popFirst(groups_division *L1,group *g);
void addFirst(groups_division *L1,group *l2);
void freeGroupsDivision(groups_division* D1);


#endif /*CLUSTERS_groups_division_H*/

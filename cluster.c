#include <stdio.h>
#include <stdlib.h>
#include "modularity.h"
#include "ERROR.h"
/*fromGroupToFile       -write in the output file the groups division*/

void fromGroupToFile(groups_division* O,char* outfile){
    group *g;
    int p;
    FILE *output;
    output = fopen(outfile,"w");
    if(output==NULL) ERROR(FILE_OPEN)
    g = O->head;
    p = fwrite(&(O->size), sizeof(int), 1, output);
    if(p!=1) ERROR(FILE_WRITE)

    while(g!=NULL) {
        p = fwrite(&(g->size), sizeof(int), 1, output);
        if(p!=1) ERROR(FILE_WRITE)

        /*add the first list to the file*/
        p = fwrite(g->grp, sizeof(int), g->size, output);
        if(p!=g->size) ERROR(FILE_WRITE)
        g = g->next;
    }
    fclose(output);
}

int main(int argc, char* argv[]) {
    groups_division *O;
    O = malloc(sizeof(groups_division));
    if(O==NULL) ERROR(ALLOC)

    if(argc != 3) ERROR(ARGUMENT)

    modularity_division(argv[1],O);
    fromGroupToFile(O,argv[2]);
    freeGroupsDivision(O);
    return 0;
}

#ifndef CLUSTERS_ERROR_H
#define CLUSTERS_ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define FILE_WRITE "Error: writing file failed\n"
#define FILE_READ "Error: read file failed\n"
#define FILE_OPEN "Error: open file failed\n"
#define DIVISION_BY_ZERO "Error: division by zero\n"
#define ALLOC "Error: allocation failed\n"
#define ZERO_VERTEX "Error: graph is empty\n"
#define ZERO_EDGES "Error: no edges in graph\n"
#define INFINITE_LOOP "Error: infinite loop\n"
#define ARGUMENT "Error: ARGUMENT\n"


#define ERROR(error) {printf("%s", error); exit(EXIT_FAILURE);}

#endif /*CLUSTERS_ERROR_H*/

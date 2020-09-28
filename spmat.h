#ifndef _SPMAT_H
#define _SPMAT_H
/*struc spmat- represent an sparse Matrix*
* add_row           - Add a new row to the sparse matrix.
* free               - Frees the sparse matrix.
* spmat_allocate     - Allocating a new sparse matrix.
 *
 * struct elem        -represent an element in the sparse Matrix*/

typedef struct _spmat {
    /* Matrix size (n*n) */
    int		n;

    /* Adds row i the matrix. Called before any other call,
     * exactly n times in order (i = 0 to n-1) */
    void	(*add_row)(struct _spmat *A, const double *row, int i);

    /* Frees all resources used by A */
    void	(*free)(struct _spmat *A);

    /* Multiplies matrix A by vector v, into result (result is pre-allocated) */
    void	(*mult)(const struct _spmat *A, const double *v, double *result);

    /* Private field for inner implementation.
     * Should not be read or modified externally */
    void	*private;
} spmat;

/* Allocates a new linked-lists sparse matrix of size n */
spmat* spmat_allocate_list(int n);


/*define the Linked list structure*/
typedef struct elem{
    double value;
    int columnIndex;
    struct elem *next;
} elem;

typedef struct elem** sp_linked; /* array of linked list*/


#endif

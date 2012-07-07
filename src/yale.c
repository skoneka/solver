/*
 * =====================================================================================
 *
 *       Filename:  yale.c
 *
 *    Description:  impementacja schematu Yale
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:27:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */
#include "yale.h"

vec_t
yale_mul_vec (yale_t y, vec_t x)
{
    int i, j;
    double v;
    vec_t m = NULL;

    m = make_vec (x->n);

    for (i = 0; i < y->cols; i++) {
        v = 0;
        for (j = y->ia[i]; j < y->ia[i + 1]; j++) {
            v += y->a[j] * x->p[y->ja[j]];
        }
        m->p[i] = v;
    }
    return m;
}


yale_t
make_yale (matrix_t m)
{
    int i, j, k;
    int elem_count = 0;
    bool bFirstInLine;
    yale_t y;

    for (j = 0; j < m->cn; j++) {
        for (i = 0; i < m->rn; i++) {
            if (matrix_get (m, i, j)) {
                elem_count++;
            }
        }
    }

    y = alloc_yale (elem_count, m->rn);

    k = 0;
    for (j = 0; j < m->cn; j++) {
        bFirstInLine = TRUE;
        for (i = 0; i < m->rn; i++) {
            if (matrix_get (m, i, j)) {
                y->a[k] = matrix_get (m, i, j);
                y->ja[k] = i;
                if (bFirstInLine) {
                    y->ia[j] = k;
                    bFirstInLine = FALSE;
                }
                k++;
            }
        }
    }
    return y;
}

void
print_yale (FILE * f, const yale_t y)
{
    int i;
    fprintf (f, "printing yale\n");

    fprintf (f, "a[] = ");
    for (i = 0; i < y->n; i++) {
        fprintf (f, "%f ", y->a[i]);
    }
    fprintf (f, "\nia[]= ");
    for (i = 0; i < y->cols; i++) {
        fprintf (f, "%d ", *(y->ia + i));
    }
    fprintf (f, "\nja[]= ");
    for (i = 0; i < y->n; i++) {
        fprintf (f, "%d ", *(y->ja + i));
    }

#ifdef DEBUG
    fprintf (f, "\nn   = %d" "\ncols= %d", y->n, y->cols);
#endif

    fprintf (f, "\n");

    return;
}

yale_t
alloc_yale (int n, int cols)
{
    int i;
    yale_t y = malloc (sizeof *y);
    y->n = n;
    y->cols = cols;
    y->a = malloc (n * sizeof (double));
    y->ia = malloc ((cols + 2) * sizeof (int));
    y->ja = malloc (n * sizeof (int));
    for (i = 0; i < y->cols; i++) {
        y->ia[i] = 0;
    }
    y->ia[cols] = n;
    for (i = 0; i < y->n; i++) {
        y->a[i] = 0;
        y->ja[i] = 0;
    }

    return y;
}

void
free_yale (yale_t y)
{
    free (y->a);
    free (y->ia);
    free (y->ja);
    free (y);

}

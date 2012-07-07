/*
 * =====================================================================================
 *
 *       Filename:  tester.c
 *
 *    Description:  moduł testujący 
 *
 *        Version:  1.0
 *        Created:  16.01.2010 20:54:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */
#include "tester.h"

struct globalArgs *ga = NULL;
FILE *out = NULL;
FILE *fmatrix = NULL;
matrix_t m0 = NULL;
yale_t y0 = NULL;
vec_t b = NULL;
vec_t x0 = NULL;
vec_t x = NULL;
vec_t r0 = NULL;
vec_t r = NULL;

int
tester_setup (struct globalArgs *gArgs)
{
    int size;
    ga = gArgs;

    ga->m_sparsity = (ga->m_sparsity > 1.0) ? 1.0 : ga->m_sparsity;
    ga->m_sparsity = (ga->m_sparsity < 0) ? 0 : ga->m_sparsity;

    if (!ga->m_static)
        srand ((int) time (NULL));

    size = ga->m_size;
    if (ga->outFile)
        out = fopen (ga->outFile, "w");
    if ((!out))
        out = stdout;

    if (!ga->matrix_auto) {

        if (ga->matrix) {
            m0 = wczytaj_matrix_plik (ga->matrix);
            if (m0->rn != m0->cn)
                return 1;
            matrix_symmetrize (m0);
            if (m0)
                size = m0->cn;
            else
                return 1;
        }

        if (ga->matrix_x) {
            x = wczytaj_vec_plik (ga->matrix_x);
            if (x)
                size = x->n;
            else
                return 1;
        }

        if (ga->matrix_x0) {
            x0 = wczytaj_vec_plik (ga->matrix_x0);

            if (x0)
                size = x0->n;
            else
                return 1;
        }
    }
    if (!m0) {
        m0 = matrix_gen_sym (size, ga->m_sparsity, ga->range_min,
                             ga->range_max, ga->diagonal, ga->nice_matrix);
    }

    y0 = make_yale (m0);

    if (!x) {
        x = vec_gen (size, ga->range_min, ga->range_max, ga->nice_matrix);
    }


    if (!x0) {
        x0 = make_vec (size);
    }

    if (m0->cn == x->n && x->n == x0->n)
        return 0;
    else
        return 1;
}

void
tester_finish ()
{
    if (out != stdout)
        fclose (out);

    if (m0)
        free_matrix (m0);
    if (y0)
        free_yale (y0);
    if (b)
        free_vec (b);
    if (x)
        free_vec (x);
    if (x0)
        free_vec (x0);
    if (r0)
        free_vec (r0);
    if (r)
        free_vec (r);
}

int
tester_run ()
{
    if (!ga->silent) {
        if (ga->verbose) {
            fprintf (out, "\nTEST RESULT:-------------------------\n");
            fprintf (out, ">>>>>> x0 = \n");
            print_vec (out, x0);
            fprintf (out, ">>>>>> A = \n");
            /*  print_yale(out,y0); */
            print_matrix (out, m0);
            fprintf (out, "multipled by:----------------------------\n");
            fprintf (out, ">>>>>> x = \n");
            print_vec (out, x);
            fprintf (out, "equals:--------------------------------\n");
            fprintf (out, ">>>>>> b = \n");
        }
    }
    if (m0) {
        free_matrix (m0);
        m0 = NULL;
    }


    r0 = yale_mul_vec (y0, x);
    if (!r0)
        return 1;

    if (!ga->silent) {
        if (ga->verbose)
            print_vec (out, r0);

        fprintf (out, "\nTESTING SOLVER: A * x = b---------------------\n");
        fprintf (out, ">>>>>> x = \n");
    }
    r = solve (y0, r0, x0, ga->max_iter, ga->precision);
    if (!r)
        return 1;


    if (!ga->silent) {
        print_vec (out, r);
        if (!ga->verbose) {
            printf (">>>>>> should be x = \n");
            print_vec (out, x);
        }
    }
    fprintf (out, "SOLVER RESULTS --check:\t\t");

    vec_cmp (r, x, ga->check) ? fprintf (out, "ARE NOT") : fprintf (out,
                                                                    "ARE");
    fprintf (out, "\t in acceptable range = %g\n", ga->check);

    fprintf (out, "SOLVER RESULTS --precision:\t");

    vec_cmp (r, x, ga->precision) ? fprintf (out, "FAIL") : fprintf (out,
                                                                     "OK");
    fprintf (out, "\t precision = %g\n", ga->precision);
    return 0;
}

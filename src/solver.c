/*
 * =====================================================================================
 *
 *       Filename:  solver.c
 *
 *    Description:  rozwiązywacz liniowych, rzadkich, symetrycznych układów równań
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:25:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#include "solver.h"


vec_t cg (yale_t A, vec_t b, vec_t x0, int max_iter, double precision);


/* 
function [x] = conjgrad(A,b,x0)
 
   r = b - A*x0;
   w = -r;
   z = A*w;
   a = (r'*w)/(w'*z);
   x = x0 + a*w;
   B = 0;
 
   for i = 1:size(A)(1);
      r = r - a*z;
      if( norm(r) < 1e-10 )
           break;
      end
      B = (r'*z)/(w'*z);
      w = -r + B*w;
      z = A*w;
      a = (r'*w)/(w'*z);
      x = x + a*w;
   end
 
end
*/

/* conjugate gradients method  */
vec_t
cg (yale_t A, vec_t b, vec_t x0, int max_iter, double precision)
{
    double norm;
    int i;
    vec_t r = NULL;
    vec_t w = NULL;
    vec_t z = NULL;
    vec_t x = NULL;
    vec_t freeme = NULL;
    vec_t freeme2 = NULL;
    vec_t freeme3 = NULL;
    double a;
    double c;

    freeme2 = yale_mul_vec (A, x0);
    r = vec_sub (b, freeme2);
    free_vec (freeme2);

    w = vec_mul_val (r, -1);

    z = yale_mul_vec (A, w);

    a = vec_mul (r, w) / vec_mul (w, z);

    freeme2 = vec_mul_val (w, a);
    x = vec_add (x0, freeme2);
    free_vec (freeme2);

    c = 0;

    for (i = 0; i < max_iter; i++) {

        freeme = r;
        freeme2 = vec_mul_val (z, a);
        r = vec_sub (r, freeme2);
        free_vec (freeme2);
        free_vec (freeme);

        if ((norm = vec_norm (r)) < precision)
            break;

        c = vec_mul (r, z) / vec_mul (w, z);

        freeme = w;
        freeme3 = vec_mul_val (w, c);
        w = vec_sub (freeme3, r);
        free_vec (freeme);
        free_vec (freeme3);

        free_vec (z);
        z = yale_mul_vec (A, w);

        a = vec_mul (r, w) / vec_mul (w, z);

        freeme = x;
        freeme2 = vec_mul_val (w, a);
        x = vec_add (x, freeme2);
        free_vec (freeme);
        free_vec (freeme2);

    }

#ifdef DBG_SOLVER
    fprintf (stderr,
             "iterated %d/%d times vec_norm(r) = %g %c precision = %g\n", i,
             max_iter, norm, (norm > precision) ? '>' : '<', precision);
#endif

    if (r)
        free_vec (r);
    if (w)
        free_vec (w);
    if (z)
        free_vec (z);

    return x;
}


vec_t
solve (yale_t a, vec_t b, vec_t x0, int max_iter, double precision)
{
    vec_t v;

    precision = (!precision) ? 1e-10 : precision;
    max_iter = (!max_iter) ? 1000 : max_iter;


    v = cg (a, b, x0, max_iter, precision);

    return v;
}

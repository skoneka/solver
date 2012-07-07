/*
 * =====================================================================================
 *
 *       Filename:  solver.h
 *
 *    Description:  rozwiązywacz liniowych, rzadkich, symetrycznych układów równań
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:24:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */

#ifndef  solver_INC
#define  solver_INC
#include "yale.h"
#include "vec.h"

/* Funkcja rozwiązująca iteracyjnie rzadkie układy równań: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t solve (yale_t a, vec_t b, vec_t x0, int max_iter, double precision);


#endif /* ----- #ifndef solver_INC  ----- */

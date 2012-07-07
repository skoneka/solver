/*
 * =====================================================================================
 *
 *       Filename:  yale.h
 *
 *    Description:  impementacja schematu Yale
 *
 *        Version:  1.0
 *        Created:  21.12.2009 17:44:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#ifndef  _yale_h__INC
#define  _yale_h__INC
#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "matrix.h"
#include "vec.h"

typedef struct yale
{
    double *a;                  /* tablica z elementami niezerowymi */
    int *ia;                    /* tablica z indeksami pierwszego niezerowego elementu w wierszu */
    int *ja;                    /* tablica z kolumnami wszystkich niezerowych elementow */
    int n;                      /* liczba elementow niezerowych */
    int cols;                   /* liczba kolumn */
} *yale_t;

/* Funkcja mnoży macierz yale przez wektor: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia*/
vec_t yale_mul_vec (yale_t y, vec_t x0);

/* Funkcja konwertuje macierz matrix_t do yale_t: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia  */
yale_t make_yale (matrix_t m);

/* Funkcja uwalnia pamięć zarezerwowaną dla struktury yale */
void free_yale (yale_t);

/* Funkcja alokuje pamięć dla struktury yale:zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
yale_t alloc_yale (int n, int ia_n);

/* Funkcja drukuje struktury yale w czytelny dla użytkownika sposób */
void print_yale (FILE * f, const yale_t y);

#endif /* ----- #ifndef _yale_h__INC  ----- */

/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  implementacja macierzy
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:23:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#ifndef _matrix_H_
#define _matrix_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "define.h"

typedef struct
{
    int rn;                     /* liczba kolumn */
    int cn;                     /* liczba wierszy */
    double **p;                 /* 2 wymiarowa tablica z elemntami */
} *matrix_t;

/* Utworz nową macierz */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t make_matrix (int, int);

/* Pobierz wartosc elementu */
double matrix_get (matrix_t a, int i, int j);

/* wygeneruj losowo symetryczną macierz */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t matrix_gen_sym (int size, double sparsity, double ra, double rb,
                         double diagonal, int pattern);

/* zsymetryzuj macierz względem diagonalnej */
void matrix_symmetrize (matrix_t a);

/* wczytaj macierz z pliku */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t wczytaj_matrix_plik (char *);

/* wczytaj macierz ze strumienia */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t wczytaj_matrix (FILE *);

/* drukuj maicerz */
void print_matrix (FILE * out, matrix_t a);

/* uwolniej zasoby macierzy */
void free_matrix (matrix_t a);


/*  zapełnij macierz wartością v */
void matrix_fill (matrix_t m, double v);

/*  skopiuj macierz */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t matrix_copy (matrix_t a);

/* pomocnicza: zapisz symetrycznie wartość */
int matrix_write_pair (matrix_t a, int x, int y, double val);

/* przemnóż macierz przez macierz */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t matrix_mul (matrix_t a, matrix_t b);

/* dodaj macierz do macierzy */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t matrix_add (matrix_t a, matrix_t b);

/* odjemij macierz od macierzy */
/* zwraca macierz lub NULL dla niepowodzenia */
matrix_t matrix_sub (matrix_t a, matrix_t b);

/* zamien wiersze w matrix; zwraca 0 lub -1 dla bledu */
int matrix_swap_row (matrix_t a, int, int);

/* zamien kolumny w matrix; zwraca 0 lub -1 dla bledu */
int matrix_swap_col (matrix_t a, int, int);

/* zapisz wartość na polu i, j macierzy */
int matrix_put (matrix_t a, int i, int j, double x);


#endif

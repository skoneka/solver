/*
 * =====================================================================================
 *
 *       Filename:  vec.h
 *
 *    Description:  implementacja wektora
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:26:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#ifndef _VEC_H_
#define _VEC_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"

typedef struct
{
    int n;                      /* liczba elementow */
    double *p;                  /* tablica elementow */
} *vec_t;

/* Funkcja porównuje dwa wektory: zwraca TRUE lub FALSE gdy wektory są inne */
bool vec_cmp (vec_t a, vec_t b, double precision);

/* Funkcja generująca losowa wektor: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t vec_gen (int size, double ra, double rb, int pattern);

/* Funkcja wylicza normę wektora */
double vec_norm (vec_t a);

/* Funkcja kopiująca wektor: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t vec_copy (vec_t a);

/* Funkcja wczytująca wektor ze strumienia: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t wczytaj_vec (FILE *);

/* Funkcja wczytująca wektor ze pliku: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t wczytaj_vec_plik (char *);

/* Funkcja mnożąca 2 wektory */
double vec_mul (vec_t a, vec_t b);

/* Funkcja mnożąca wektor przez liczbę: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t vec_mul_val (vec_t a, double val);

/* Funkcja dodająca wektor do wektora: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t vec_add (vec_t a, vec_t b);

/* Funkcja odejmująca wektor od wektora: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t vec_sub (vec_t a, vec_t b);

/* Funkcja pobiera z wektora element o indeksie i */
double vec_get (vec_t a, int i);

/* Funkcja zapisuje wartość do wektora w indeksie i: zwraca TRUE dla niepowodzenia  */
int vec_put (vec_t a, int i, double x);

/* Funkcja mnożąca wektor przez liczbę: zwraca wskaźnik na wektor lub NULL w razie niepowodzenia */
vec_t make_vec (int);

/*Funkcja uwalnia pamięć zaalokowaną dla wektora  */
void free_vec (vec_t a);

/*Funkcja drukuje wektor do strumienia */
void print_vec (FILE * out, vec_t a);

#endif

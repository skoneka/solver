/*
 * =====================================================================================
 *
 *       Filename:  tester.h
 *
 *    Description:  moduł testujący 
 *
 *        Version:  1.0
 *        Created:  16.01.2010 20:55:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#ifndef  tester_INC
#define  tester_INC
#include "tester.h"

#include "define.h"
#include "yale.h"
#include "matrix.h"
#include "vec.h"
#include "solver.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct globalArgs
{
    /* FLAGI */
    bool verbose;
    bool silent;
    bool nice_matrix;           /* losuj liczby całkowite */
    bool show_help;
    bool m_static;              /* nie inicjuj generatora liczb losowych */
    bool matrix_auto;           /* ignoruj dane wejściowe */

    char *outFile;              /* plik wyjściowy */
    char *matrix;               /* plik z macierza */
    char *matrix_x;             /* plik z wektorem wynikowym */
    char *matrix_x0;            /* plik z wektorem startowym */
    int m_size;                 /* rozmiar losowanej macierzy */
    double m_sparsity;          /* rzadkość losowanej macierzy */
    double check;               /* dokładność porównywania macierzy 
                                   wynikowej i wzoru */
    double precision;           /* dokładność do jakiej funkcji rozwiązującej */
    int max_iter;               /* maksymalna liczba iteracji */
    double range_min;           /* maksymalna losowana liczba */
    double range_max;           /* minimalna losowana liczba  */
    double diagonal;            /* wartost jakimi wypełniana jest diagonalna */

};

/* Funkcja wczytuje dane na podstawie struktury globalArgs: w razie niepowodzenia zwraca prawdę */
int tester_setup (struct globalArgs *gArgs);

/* Funkcja uwalnia zasoby testera */
void tester_finish ();

/* Funkcja uruchamia tester: w razie niepowodzenia zwraca prawdę */
int tester_run ();

#endif /* ----- #ifndef tester_INC  ----- */

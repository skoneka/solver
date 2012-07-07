/*
 * =====================================================================================
 *
 *       Filename:  vec.c
 *
 *    Description:  implementacja wektora
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:26:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#include "vec.h"

bool
vec_cmp (vec_t a, vec_t b, double precision)
{
    int i;
    if (a->n != b->n)
        return TRUE;
    for (i = 0; i < a->n; i++)

        if ((a->p[i] > b->p[i] + precision)
            || (a->p[i] < b->p[i] - precision))
            return TRUE;
    return FALSE;
}

vec_t
vec_gen (int size, double ra, double rb, int pattern)
{
    int i;
    double tmp = 0;
    vec_t m = NULL;
    m = make_vec (size);

    for (i = 0; i < m->n; i++) {
        tmp = (ra + (rb - ra) * ((double) rand () / (double) RAND_MAX));
        if (pattern)
            tmp = floor (tmp);
        vec_put (m, i, tmp);
    }
    return m;
}

double
vec_norm (vec_t a)
{
    int i;
    double s = 0;
    for (i = 0; i < a->n; i++) {
        s += vec_get (a, i) * vec_get (a, i);
    }
    return sqrt (s);
}

vec_t
vec_copy (vec_t a)
{
    int i;
    vec_t m = NULL;
    m = make_vec (a->n);
    for (i = 0; i < a->n; i++)
        vec_put (m, i, vec_get (a, i));
    return m;
}


vec_t
vec_mul_val (vec_t a, double val)
{
    int i;
    vec_t mret;

    if (!(mret = make_vec (a->n)))
        return NULL;

    for (i = 0; i < a->n; i++) {
        vec_put (mret, i, vec_get (a, i) * val);
    }
    return mret;
}

double
vec_mul (vec_t a, vec_t b)
{
    int i;
    double mret = 0;

    for (i = 0; i < b->n; i++) {
        mret += vec_get (a, i) * vec_get (b, i);
    }
    return mret;
}

vec_t
vec_add (vec_t a, vec_t b)
{
    int i;
    vec_t mret = NULL;
    mret = make_vec (b->n);

    if (!mret)
        return NULL;

    for (i = 0; i < b->n; i++) {
        vec_put (mret, i, vec_get (a, i) + vec_get (b, i));
    }
    return mret;
}

vec_t
vec_sub (vec_t a, vec_t b)
{
    int i;
    vec_t mret;

    if (!(mret = make_vec (b->n)))
        return NULL;

    for (i = 0; i < b->n; i++) {
        vec_put (mret, i, vec_get (a, i) - vec_get (b, i));
    }
    return mret;
}

/* utworz vec o rozmiarach rn cn; zwraca NULL dla niepowodzenia */
vec_t
make_vec (int n)
{
    vec_t nm = malloc (sizeof *nm);

    if (!nm)
        return NULL;

    if (!(nm->p = malloc ((n + 1) * sizeof *nm->p))) {
        free (nm);
        return NULL;
    }


    nm->n = n;
    return nm;
}

/* zwolnij pamiec zajmowana przez vec */
void
free_vec (vec_t a)
{
    if (!a)
        return;
    free (a->p);
    free (a);
}

int
vec_put (vec_t a, int i, double x)
{
    /*  printf("\nvec_put()"); */
    if (i >= 0 && i < (*a).n) {
        (*a).p[i] = x;
        return FALSE;
    }
    else {
        return TRUE;
    }
}

double
vec_get (vec_t a, int i)
{
    return (*a).p[i];
    /* return a->p[i][j]; */
}

/*wczytaj vec ze strumienia; zwraca wskaznik do vec_t lub NULL dla niepowodzenia*/
vec_t
wczytaj_vec (FILE * p)
{
    int n, m, i, j;             /* zmienne robocze */
    vec_t vec;

    if (fscanf (p, "%i x %i", &n, &m) != 2)
        return NULL;
    if (!(vec = make_vec (m)))
        return NULL;

    while ((i = fgetc (p)) == ' ')      /* pomijamy spacje po liczbie elementow */
        ;

    /* mamy znak rozny od spacji - powinien to byc znak '[' */
    if (i != '[') {
        free_vec (vec);
        return NULL;            /* nie jest - bledny format pliku */
    }

    /* teraz czytamy n liczb */
    for (j = 0; j < m; j++) {
        for (i = 0; i < n; i++) {
            float tmpval = 0;
            if (fscanf (p, "%f", &tmpval) != 1) {       /* fscanf powinno zawsze zwracac 1 - jesli zwroci cos innego */
                free_vec (vec);
                return NULL;    /* to znaczy, ze format pliku jest zly */
            }
            else {
                vec_put (vec, j, tmpval);
            }
        }
    }

    /* mamy liczby, teraz szukamy zamykajacego nawiasu: */
    while ((i = fgetc (p)) == ' ' || i == '\n') /* pomijamy spacje i \n */
        ;

    /* mamy znak rozny od spacji - powinien to byc znak ']' */
    if (i != ']') {
        free_vec (vec);
        return NULL;            /* nie jest - bledny format pliku */
    }
    /* jesli doszlismy juz tu, to wszystko jest ok, mamy w wektorze n liczb */
    return vec;
}

/*wczytaj vec z pliku; zwraca wskaznik do vec_t lub NULL dla niepowodzenia*/
vec_t
wczytaj_vec_plik (char *filename)
{
    vec_t m;
    FILE *f;
    if (!(f = fopen (filename, "r")))
        return NULL;
    m = wczytaj_vec (f);
    fclose (f);
    return m;
}


/* drukuj vec do strumenia */
void
print_vec (FILE * out, vec_t a)
{
    int i;
    if (a == NULL) {
        fprintf (stderr, "! print_vec() - vec does not exist.\n");
        return;
    }
    fprintf (out, "1 x %d [\n", a->n);

    for (i = 0; i < a->n; i++) {
        fprintf (out, "%g ", vec_get (a, i));
#ifdef MATLAB
        fprintf (out, "\n");
#endif
    }
#ifndef MATLAB
    fprintf (out, "\n");
#endif
    fprintf (out, "]\n");
}

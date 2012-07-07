/*
 * =====================================================================================
 *
 *       Filename:  matrix.c
 *
 *    Description:  implementacja macierzy
 *
 *        Version:  1.0
 *        Created:  23.01.2010 17:24:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Artur Skonecki (), 
 *        Company:  adb.cba.pl
 *
 * =====================================================================================
 */


#include "matrix.h"

#define matrix_insert(a,i,j,x) matrix_put(a,i,j,x)

matrix_t
matrix_copy (matrix_t a)
{
    int i, j;
    matrix_t m = NULL;
    m = make_matrix (a->rn, a->cn);
    for (j = 0; j < a->cn; j++)
        for (i = 0; i < a->rn; i++)
            matrix_put (m, i, j, matrix_get (a, i, j));
    return m;
}

int
matrix_write_pair (matrix_t a, int x, int y, double val)
{
    matrix_put (a, x, y, val);
    matrix_put (a, y, x, val);
    return 0;
}

matrix_t
matrix_gen_sym (int size, double sparsity, double ra, double rb,
                double diagonal, int pattern)
{
    double tmp;
    int i, j, k;
    matrix_t m = NULL;
    int chance = 1 / sparsity;
    bool bWrite = FALSE;
    m = make_matrix (size, size);

    k = 0;
    for (j = 0; j < m->cn; j++) {
        for (i = k; i < m->rn; i++) {
            if ((bWrite = (rand () % chance == 0) ? TRUE : FALSE)) {
                tmp =
                    (ra + (rb - ra) * ((double) rand () / (double) RAND_MAX));
                if (pattern)
                    tmp = floor (tmp);
                matrix_put (m, i, j, tmp);

            }
            if (i == j)
                matrix_put (m, i, j, diagonal);
        }
        k++;
    }
    matrix_symmetrize (m);
    return m;
}

void
matrix_symmetrize (matrix_t a)
{
    int i, j, k;

    k = 0;
    for (j = 0; j < a->cn; j++) {
        for (i = k; i < a->rn; i++) {
            if (i != j)
                matrix_write_pair (a, i, j, matrix_get (a, i, j));
        }
        k++;
    }
}


/* pomnoz dwie matrixe i zwroc do matrix wynikowa lub NULL w razie bledu */
matrix_t
matrix_mul (matrix_t a, matrix_t b)
{
    int i, j, k;
    matrix_t mret;

    if (a->rn != b->cn) {
        fprintf (stderr, "! matrixe nieprawidlowych rozmiarow.");
        return NULL;
    }
    if (!(mret = make_matrix (b->rn, b->cn)))
        return NULL;

    for (i = 0; i < b->cn; i++) {
        for (j = 0; j < b->rn; j++) {
            matrix_insert (mret, i, j, 0);
            for (k = 0; k < a->cn; k++) {
                mret->p[i][j] += a->p[k][i] * b->p[j][k];
            }
        }
    }


    return mret;
}

matrix_t
matrix_sub (matrix_t a, matrix_t b)
{
    int i, j;
    matrix_t mret;

    if (!(mret = make_matrix (b->rn, b->cn)))
        return NULL;

    for (j = 0; j < b->cn; j++) {
        for (i = 0; i < b->rn; i++) {
            matrix_put (mret, i, j,
                        matrix_get (a, i, j) - matrix_get (b, i, j));
        }
    }
    return mret;
}

matrix_t
matrix_add (matrix_t a, matrix_t b)
{
    int i, j;
    matrix_t mret;

    if (!(mret = make_matrix (b->rn, b->cn)))
        return NULL;

    for (j = 0; j < b->cn; j++) {
        for (i = 0; i < b->rn; i++) {
            matrix_put (mret, i, j,
                        matrix_get (a, i, j) + matrix_get (b, i, j));
        }
    }
    return mret;
}


/* zamien wiersze w matrix; zwraca 0 lub -1 dla bledu */
int
matrix_swap_row (matrix_t a, int source, int target)
{
    int i;
    int mwidth = (*a).rn;
    matrix_t m_tmp;
    if (source == target)
        return 0;

    if (!(m_tmp = make_matrix (mwidth, 1)))
        return -1;
    for (i = 0; i < mwidth; i++)
        matrix_insert (m_tmp, i, 0, matrix_get (a, i, source));
    for (i = 0; i < mwidth; i++)
        matrix_insert (a, i, source, matrix_get (a, i, target));
    for (i = 0; i < mwidth; i++)
        matrix_insert (a, i, target, matrix_get (m_tmp, i, 0));
    free_matrix (m_tmp);
    return 0;
}

/* zamien kolumny w matrix; zwraca 0 lub -1 dla bledu */
int
matrix_swap_col (matrix_t a, int source, int target)
{
    int i;
    int mwidth = (*a).cn;
    matrix_t m_tmp;
    if (source == target)
        return 0;
    if (!(m_tmp = make_matrix (1, mwidth)))
        return -1;
    for (i = 0; i < mwidth; i++)
        matrix_insert (m_tmp, 0, i, matrix_get (a, source, i));
    for (i = 0; i < mwidth; i++)
        matrix_insert (a, source, i, matrix_get (a, target, i));
    for (i = 0; i < mwidth; i++)
        matrix_insert (a, target, i, matrix_get (m_tmp, 0, i));
    free_matrix (m_tmp);
    return 0;
}

/* utworz matrix o rozmiarach rn cn; zwraca NULL dla niepowodzenia */
matrix_t
make_matrix (int rn, int cn)
{
    int i;
    matrix_t nm;

    if (!(nm = malloc (sizeof *nm)))
        return NULL;

    if (!(nm->p = malloc (rn * sizeof *nm->p))) {
        free (nm);
        return NULL;
    }

    for (i = 0; i < rn; i++) {
        if (!(nm->p[i] = malloc ((cn) * sizeof *nm->p[i]))) {
            int j;
            for (j = 0; j < i; j++)
                free (nm->p[j]);
            free (nm->p);
            free (nm);
            return NULL;
        }
    }

    nm->cn = cn;
    nm->rn = rn;
    matrix_fill (nm, 0);
    return nm;
}

void
matrix_fill (matrix_t m, double v)
{
    int i, j;
    for (j = 0; j < m->cn; j++) {
        for (i = 0; i < m->rn; i++) {
            matrix_put (m, i, j, v);
        }
    }
}

/* zwolnij pamiec zajmowana przez matrix */
void
free_matrix (matrix_t a)
{
    int i;
    for (i = 0; i < a->rn; i++)
        free (a->p[i]);
    free (a->p);
    free (a);
}

/*wsadz a->p[i][j] =x, zwraca 1 dla niepowodzenia */
int
matrix_put (matrix_t a, int i, int j, double x)
{
    /*  printf("\ninsert()"); */
    if (i >= 0 && i < (*a).rn && j >= 0 && j < (*a).cn) {
        (*a).p[i][j] = x;
        return 0;
    }
    else {
        return 1;
    }
}

/* wez  a->p[i][j]*/
double
matrix_get (matrix_t a, int i, int j)
{
    return (*a).p[i][j];
    /* return a->p[i][j]; */
}

/*wczytaj matrix ze strumienia; zwraca wskaznik do matrix_t lub NULL dla niepowodzenia*/
matrix_t
wczytaj_matrix (FILE * p)
{
    int n, m, i, j;             /* zmienne robocze */
    matrix_t matrix;

    if (fscanf (p, "%i x %i", &n, &m) != 2)
        return NULL;
    if (!(matrix = make_matrix (n, m)))
        return NULL;

    while ((i = fgetc (p)) == ' ')      /* pomijamy spacje po liczbie elementow */
        ;

    /* mamy znak rozny od spacji - powinien to byc znak '[' */
    if (i != '[') {
        free_matrix (matrix);
        return NULL;            /* nie jest - bledny format pliku */
    }

    /* teraz czytamy n liczb */
    for (j = 0; j < m; j++) {
        for (i = 0; i < n; i++) {
            float tmpval = 0;
            if (fscanf (p, "%f", &tmpval) != 1) {       /* fscanf powinno zawsze zwracac 1 - jesli zwroci cos innego */
                free_matrix (matrix);
                return NULL;    /* to znaczy, ze format pliku jest zly */
            }
            else {
                matrix_insert (matrix, i, j, tmpval);
            }
        }
    }

    /* mamy liczby, teraz szukamy zamykajacego nawiasu: */
    while ((i = fgetc (p)) == ' ' || i == '\n') /* pomijamy spacje i \n */
        ;

    /* mamy znak rozny od spacji - powinien to byc znak ']' */
    if (i != ']') {
        free_matrix (matrix);
        return NULL;            /* nie jest - bledny format pliku */
    }
    /* jesli doszlismy juz tu, to wszystko jest ok, mamy w wektorze n liczb */
    return matrix;
}

/*wczytaj matrix z pliku; zwraca wskaznik do matrix_t lub NULL dla niepowodzenia*/
matrix_t
wczytaj_matrix_plik (char *filename)
{
    matrix_t m;
    FILE *f;
    if (!(f = fopen (filename, "r")))
        return NULL;
    m = wczytaj_matrix (f);
    fclose (f);
    return m;
}


/* drukuj matrix do strumenia */
void
print_matrix (FILE * out, matrix_t a)
{
    int i, j;
    if (a == NULL) {
        fprintf (stderr, "! print_matrix() - matrix does not exist.\n");
        return;
    }
    fprintf (out, "%d x %d [\n", a->rn, a->cn);

    for (j = 0; j < a->cn; j++) {
        for (i = 0; i < a->rn; i++) {
            fprintf (out, "%g ", matrix_get (a, i, j));
        }
        fprintf (out, "\n");
    }
    fprintf (out, "]\n");
}

#include <stdio.h>
#include <math.h>
#include <assert.h>

//-----------------------------------------------------------------------------

#define INFINITE -1
#define INFELICITY 1E-6

//-----------------------------------------------------------------------------

int solve_linear (double, double, double*); // solves linear equation
int solve_square (double, double, double, double*, double*); // solves square equation
int input_double (char [], double*); // responsible for entering
void normalize (double*, double*, double*); // normalizing of coefficients
int is_zero (double); // compare real number with zero excluding infelicity

//-----------------------------------------------------------------------------

int main ()
{
    printf ("# Square equation solver (c) SaintAleksei\n"
            "#\n"
            "# Enter coefficients from ax^2 - bx + c = 0:\n"
            "#\n"                                           );

    double a, b, c;
    input_double ("a", &a);
    input_double ("b", &b);
    input_double ("c", &c);

    double root1, root2;
    int r_count;
    r_count = solve_square (a, b, c, &root1, &root2);

    switch (r_count)
    {
        case 0:        printf ("# Your equation has no roots");
                       break;

        case 1:        printf ("# The root of your equation is %lg", root1);
                       break;

        case 2:        printf ("# The roots of your equation are %lg and %lg", root1, root2);
                       break;

        case INFINITE: printf ("# Your equation has infinite number of roots");
                       break;

        default:       printf ("# Oooops... Something went wrong:\n"
                               "# main(): r_count = %d", r_count);
    }

    return 0;
}

//-----------------------------------------------------------------------------

int solve_linear (double a, double b, double* root_ad)
{
    if (is_zero (a) && is_zero (b))
        return INFINITE;

    if (is_zero (a) && !is_zero (b))
        return 0;

    *root_ad = -b / a;

    return 1;
}

//-----------------------------------------------------------------------------

int solve_square (double a, double b, double c, double* root1_ad, double* root2_ad)
{
    if (is_zero (a))
        return solve_linear (b, c, root1_ad);

    double discr = (b * b) - (4 * a * c);

    if (is_zero (discr))
    {
        *root1_ad = -b / (2 * a);

        return 1;
    }

    if (discr < 0)
        return 0;

    *root1_ad = (-b + sqrt (discr) / (2 * a));
    *root2_ad = (-b - sqrt (discr) / (2 * a));

    return 2;
}

//-----------------------------------------------------------------------------

int input_double (char name[], double* value)
{
    printf ("# %s = ", name);

    if (!scanf ("%lg", value))
    {
        printf ("# Invalid input: enter a real numbers:\n");

        fflush (stdin);

        return input_double (name, value);
    }

    return 0;
}

//-----------------------------------------------------------------------------

void normalize (double* a, double* b, double* c)
{
    double x, y;
    x = *b / *a;
    y = *c / *a;

    if (isfinite (x) && isfinite (y))
        {
            *b = *b / *a;
            *c = *c / *a;
            *a = 1;
            return;
        }

    x = *c / *b;

    if (isfinite (x))
        {
            *c = *c / *b;
            *b = 1;
        }
}

//-----------------------------------------------------------------------------

int is_zero (double a)
{
    return fabs (a - 0) <= INFELICITY ? 1 : 0;
}




#include <stdio.h>
#include <math.h>
#include <assert.h>

//-----------------------------------------------------------------------------

#define INFINITE -1
#define INFELICITY 1E-7

//-----------------------------------------------------------------------------

int solve_linear (double, double, double*); // solves linear equation
int solve_square (double, double, double, double*, double*); // solves square equation
int comparsion (double, double); // compares two real numbers excluding infelicity
int input_double (char [], double*); // responsible for entering

//-----------------------------------------------------------------------------

int main()
{
    int r_count = 0;
    double a = 0, b = 0, c = 0, root1 = 0, root2 = 0;

    printf ("# Square equation solver (c) SaintAleksei\n"
            "#\n"
            "# Enter coefficients from ax^2 - bx + c = 0:\n"
            "#\n"                                           );

    input_double ("a", &a);
    input_double ("b", &b);
    input_double ("c", &c);

    printf ("# \n");

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

/*
    This function compares 2 double numbers taking into account infelicity
    input parameters: double a and double b - compared numbers
    Output parameters: -
    return: 0 means a == b, 1 means a > b, -1 means a < b
*/

int comparsion (double a, double b)
{
    if (fabs (a - b) <= INFELICITY)
        return 0;
    if (a > b)
        return 1;
    if (a < b)
        return -1;

    return 0;
}

//-----------------------------------------------------------------------------

/*
    This function solves linear equation of the form ax + b = 0
    Input parameters: double a and double b - coefficients of the equation
    Output parameters: double* root_ad - memory address at which the root of the equation will be written
    Return: number of roots ( 0 or 1 or INFINITE = -1, that means infinite number of roots)
*/

int solve_linear (double a, double b, double* root_ad)
{
    if (comparsion (a, 0) == 0 && comparsion (b, 0) == 0)
        return INFINITE;

    if (comparsion (a, 0) == 0 && comparsion (b, 0) != 0)
        return 0;

    *root_ad = -b / a;

    return 1;
}

//-----------------------------------------------------------------------------

/*
    This function solves linear equation of the form ax^2 + bx + c = 0
    Input parameters: double a and double b and double c - coefficients of the equation
    Output parameters: double* root1_ad and double* root2_ad - memory addresses  at which the roots of the equation will be written
    Return: number of roots (0, 1, 2) or solve_linear (b, c, root1_ad) (if square equation is reduced to linear)
*/

int solve_square (double a, double b, double c, double* root1_ad, double* root2_ad)
{
    if (comparsion (a, 0) == 0)
        return solve_linear (b, c, root1_ad);

    double discr = b * b - 4 * a * c;

    if (comparsion (discr, 0) == -1)
        return 0;
    if (comparsion (discr, 0) == 0)
    {
        *root1_ad = -b / (2 * a);

        return 1;
    }

    *root1_ad = (-b + sqrt (discr) / (2 * a));
    *root2_ad = (-b - sqrt (discr) / (2 * a));

    return 2;
}

//-----------------------------------------------------------------------------

/*
    This function is responsible for the correctness of double data entry
    Input parameters: char name[] - the name of the entered number
    Output parameters: double* value - memory address to which data will be saved
    Return: 0 - everything is good
*/

int input_double (char name[], double* value)
{
    printf ("# %s = ", name);

    if (!scanf ("%lg", value))
    {
        printf ("# Invalid input: enter a real numbers:\n");

        char line[1000];
        fgets (line, 1000, stdin);

        return input_double (name, value);
    }

    return 0;
}




# include <stdio.h>

//-----------------------------------------------------------------------------

// This function checks the correctness of the input data

int input_double (char name, double* value)
{

    printf ("# %c = ", name);

    if (!scanf ("%lg", value))
    {

        printf ("# Invalid input: enter a real numbers:\n");

        return input_double (name, value);

    }

    return 0;

}

//-----------------------------------------------------------------------------

int main()
{

    double a;

    input_double('a', &a);

    return 0;

}


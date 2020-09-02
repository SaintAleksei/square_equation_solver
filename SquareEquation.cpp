#include <stdio.h>
#include <math.h>
#include <assert.h>


//-----------------------------------------------------------------------------


const int INFINITE = -1;

const double INFELICITY = 1E-6;


//-----------------------------------------------------------------------------


int square_equation (double a, double b, double c, double* x1, double* x2);

int comparsion (double a, double b);


//-----------------------------------------------------------------------------


int main()
  {
  printf ("# This is a simple program that solves simple square equations of the form ax^2+bx+c=0\n\n");

  printf ("# Enter a, b, c:\n"
          "# " );

  double a = 0, b = 0, c = 0;

  scanf ("%lg %lg %lg", &a, &b, &c);

  double x1 = 0, x2 = 0;

  int rcount = square_equation(a, b, c, &x1, &x2);

  switch (rcount)
    {

    case 0: printf ("# There are no roots of your equation");

            break;

    case 1: printf ("# The root of your equation is %lg", x1);

            break;

    case 2: printf ("# The roots of your equation are %lg and %lg", x1, x2);

            break;

    case INFINITE: printf ("# Your equation have an infinite number of roots");

             break;

    default: printf ("# Oooops... Something went wrong, rcount = %d", rcount);

             return 1;

    }

  return 0;
  }


//-----------------------------------------------------------------------------

//! \brief Эта функция сравнивает два вещественных числа
//! \param[in] a и b - входящие параметры (сравниваемые числа)
//! \return 0 - a = b, 1 - a > b, -1 - b > a

int comparsion (double a, double b)
  {
  if (fabs (a - b) < INFELICITY)
    {
    return 0;
    }

  if (a < b)
    {
    return -1;
    }

  if (a > b)
    {
    return 1;
    }
  }


//-----------------------------------------------------------------------------

//! \brief Эта функция решает квадратное уравнение ax^2+bx+c=0
//! \param[in] a, b, c - входящие параметры (коэффиценты уравнения)
//! \param[out] x1, x2 - исходящие параметры (корни уравнения)
//! \return Функция возвращает количество корней уравнения, либо константу INFINITE, если их бесконечно много

int square_equation(double a, double b, double c, double* x1, double* x2)
  {
  assert (isfinite (a));
  assert (isfinite (b));
  assert (isfinite (c));

  assert (x1 != NULL);
  assert (x2 != NULL);
  assert (x1 != x2);

  double discr = b * b - 4 * a * c;

  int result = comparsion(a, 0);

  if (result == 0)
    {
    result = comparsion(b, 0);

    if (result == 0)
      {
      result = comparsion(c, 0);

      return (result == 0)? INFINITY : 0;
      }
    else
      {
      *x1 = -c / b;

      return 1;
      }
    }

  result = comparsion(discr, 0);

  switch (result)
    {
    case 0: *x1 = -b / (2 * a);

            return 1;

    case 1: *x1 = (-b + sqrt(discr)) / (2 * a);
            *x2 = (-b - sqrt(discr)) / (2 * a);

            return 2;

    case -1: return 0;

    }
  }

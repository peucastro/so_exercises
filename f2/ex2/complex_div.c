#include <math.h>
#include "complex.h"

complex *complex_div(complex *z, complex *w)
{
    double a = z->x, b = z->y, c = w->x, d = w->y;

    return complex_new((a * c + b * d) / (pow(c, 2) + pow(d, 2)), (b * c - a * d) / (pow(c, 2) + pow(d, 2)));
}

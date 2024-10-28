#include "vector.h"
#include <math.h>

double vector_mod(vector *v) {
  return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

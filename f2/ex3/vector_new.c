#include "vector.h"
#include <stdlib.h>

vector *vector_new(double x, double y, double z) {
  vector *w = (vector *)malloc(sizeof(vector));
  w->x = x;
  w->y = y;
  w->z = z;
  return w;
}

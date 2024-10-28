#include "list.h"
#include <stdlib.h>

list *list_new_random(int size, int range) {
  list *l = list_new();
  for (int i = 0; i < size; i++)
    list_add_first(rand() % range, l);
  return l;
}

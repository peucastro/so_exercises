#include "list.h"
#include <stdlib.h>

int list_get_last(list *l) {
  /* assumes list l is not empty */
  node *q = l->first;
  while (q->next != NULL)
    q = q->next;

  return q->val;
}

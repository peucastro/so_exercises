#include <stdlib.h>
#include "list.h"

void list_add_first(int val, list *l)
{
    node *p = node_new(val, NULL);
    if (l->size == 0)
    {
        l->first = p;
    }
    else
    {
        p->next = l->first;
        l->first = p;
    }
    l->size++;
}

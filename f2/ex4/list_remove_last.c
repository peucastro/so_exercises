#include <stdlib.h>
#include "list.h"

void list_remove_last(list *l)
{
    /* assumes list l is not empty */
    node *p = l->first;
    if (p->next == NULL)
    {
        l->first = NULL;
        free(p);
    }
    else
    {
        while (p->next->next != NULL)
            p = p->next;

        node *q = p->next;
        p->next = NULL;
        free(q);
    }
    l->size--;
}

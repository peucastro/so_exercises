#include <stdio.h>
#include "list.h"

void list_print(list *l)
{
    if (l->size == 0)
        return;

    node *q = l->first;
    while (q->next != NULL)
    {
        printf("%d -> ", q->val);
        q = q->next;
    }
    printf("%d\n", q->val);
}

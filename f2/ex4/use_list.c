#include <stdio.h>
#include "list.h"

int main(int argc, char **argv)
{
    // Creating lists
    list *l1 = list_new();
    list *l2 = list_new_random(5, 100);

    // Adding elements to l1
    list_add_first(30, l1);
    list_add_last(10, l1);
    list_add_first(50, l1);

    // Checking and printing l1 contents before deletion
    printf("l1 contents before deletion: ");
    list_print(l1);

    int first_l1 = list_get_first(l1);
    int last_l1 = list_get_last(l1);
    int size_l1 = list_size(l1);

    // Printing first, last, and size of l1 before deletion
    printf("First element of l1: %d\n", first_l1);
    printf("Last element of l1: %d\n", last_l1);
    printf("Size of l1 before deletion: %d\n", size_l1);

    // Removing elements from l1
    list_remove_first(l1);
    list_remove_last(l1);

    // Checking and printing l1 contents after deletion
    printf("\nl1 contents after deletion: ");
    list_print(l1);

    int size_l1_after = list_size(l1);
    printf("Size of l1 after deletion: %d\n", size_l1_after);

    // Printing random list l2
    printf("\nl2 contents (random list): ");
    list_print(l2);

    int size_l2 = list_size(l2);
    int first_l2 = list_get_first(l2);
    int last_l2 = list_get_last(l2);

    // Printing first, last, and size of l2
    printf("First element of l2: %d\n", first_l2);
    printf("Last element of l2: %d\n", last_l2);
    printf("Size of l2: %d\n", size_l2);

    // Removing elements from l2
    list_remove_first(l2);
    list_remove_last(l2);

    // Checking and printing l1 contents after deletion
    printf("\nl2 contents after deletion: ");
    list_print(l2);

    int size_l2_after = list_size(l2);
    printf("Size of l2 after deletion: %d\n", size_l2_after);

    return 0;
}

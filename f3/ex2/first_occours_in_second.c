#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *p = strdup(argv[1]);

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(p, argv[i]) == 0)
        {
            printf("%s occours in the second string!\n", p);
            return 0;
        }
    }

    printf("%s doesn't occours in the second string!\n", p);
    return 0;
}

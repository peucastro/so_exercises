#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *p = strdup(argv[1]);

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        p[i] = tolower(p[i]);
    }

    printf("%s\n", p);

    return 0;
}

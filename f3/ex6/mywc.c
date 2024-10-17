#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3 || argv[1][0] != '-' || !(argv[1][1] == 'c' || argv[1][1] == 'w' || argv[1][1] == 'l'))
    {
        printf("Correct usage: ./mywc -flag filename\n\nFlag options:\n    -c : prints the number of characters in the file\n    -w : prints the number of words in the file\n    -l : prints the number of lines in the file\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int count = 0;

    if (argv[1][1] == 'c')
    {
        for (char c = getc(file); c != EOF; c = getc(file))
            count++;
    }
    else if (argv[1][1] == 'w')
    {
        for (char c = getc(file); c != EOF; c = getc(file))
            if (c == ' ')
                count++;
        count++;
    }
    else if (argv[1][1] == 'l')
    {
        for (char c = getc(file); c != EOF; c = getc(file))
            if (c == '\n')
                count++;
    }

    printf("%d\n", count);
    exit(EXIT_SUCCESS);
}

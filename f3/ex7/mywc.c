#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int cflag = 0;
    int wflag = 0;
    int lflag = 0;

    int c;
    while ((c = getopt(argc, argv, "cwl")) != -1)
    {
        switch (c)
        {
        case 'c':
            cflag = 1;
            break;
        case 'w':
            wflag = 1;
            break;
        case 'l':
            lflag = 1;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    char *filename = argv[argc - 1];
    if (filename == NULL)
    {
        printf("usage: %s [-c|-w|-l] file\n\nFlag options:\n    -c : prints the number of characters in the file\n    -w : prints the number of words in the file\n    -l : prints the number of lines in the file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int count;

    if (cflag)
    {
        count = 0;
        for (char c = getc(file); c != EOF; c = getc(file))
            count++;
        printf("Characters count: %d\n", count);
    }
    if (wflag)
    {
        rewind(file);
        count = 0;
        for (char c = getc(file); c != EOF; c = getc(file))
            if (c == ' ' || c == '\n' || c == '\t')
                count++;
        printf("Words count: %d\n", count);
    }
    if (lflag)
    {
        rewind(file);
        count = 0;
        for (char c = getc(file); c != EOF; c = getc(file))
            if (c == '\n')
                count++;
        printf("Lines count: %d\n", count);
    }

    fclose(file);
    exit(EXIT_SUCCESS);
}

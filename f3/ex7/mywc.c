#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int getwords(char *line)
{
    int nwords = 0;
    char *word;

    while ((word = strsep(&line, " \t")) != NULL)
    {
        if (*word == '\0')
            continue;
        nwords++;
    }

    return nwords;
}

int main(int argc, char *argv[])
{
    bool cflag = false;
    bool wflag = false;
    bool lflag = false;

    int c;
    while ((c = getopt(argc, argv, "cwl")) != -1)
    {
        switch (c)
        {
        case 'c':
            cflag = true;
            break;
        case 'w':
            wflag = true;
            break;
        case 'l':
            lflag = true;
            break;
        default:
            printf("usage: %s [-c|-w|-l] file\n\nFlag options:\n    -c : prints the number of characters in the file\n    -w : prints the number of words in the file\n    -l : prints the number of lines in the file\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    FILE *file = fopen(argv[argc - 1], "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int nchars = 0;
    int nwords = 0;
    int nlines = 0;

    ssize_t read;
    size_t size = 0;
    char *line = NULL;

    while ((read = getline(&line, &size, file)) != -1)
    {
        nchars += read;
        nwords += getwords(line);
        nlines++;
    }

    if (cflag)
    {
        printf("Chars count: %d\n", nchars);
    }
    if (wflag)
    {
        rewind(file);
        printf("Words count: %d\n", nwords);
    }
    if (lflag)
    {
        rewind(file);
        printf("Lines count: %d\n", nlines);
    }

    fclose(file);
    exit(EXIT_SUCCESS);
}

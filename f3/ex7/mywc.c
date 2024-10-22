#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int calculate_chars(FILE *file)
{
    int count = 0;

    for (char c = getc(file); c != EOF; c = getc(file))
        count++;

    return count;
}

int calculate_words(FILE *file)
{
    ssize_t read;
    size_t size = 0;
    char *line = NULL;
    char *word = NULL;
    int count = 0;

    while ((read = getline(&line, &size, file)) != -1)
    {
        while ((word = strsep(&line, " \t")) != NULL)
        {
            if (*word == '\0')
                continue;
            count++;
        }
    }

    return count;
}

int calculate_lines(FILE *file)
{
    ssize_t read;
    size_t size = 0;
    char *line = NULL;
    int count = 0;

    while ((read = getline(&line, &size, file)) != -1)
        count++;

    return count;
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

    if (cflag)
    {
        printf("Characters count: %d\n", calculate_chars(file));
    }
    if (wflag)
    {
        rewind(file);
        printf("Words count: %d\n", calculate_words(file));
    }
    if (lflag)
    {
        rewind(file);
        printf("Lines count: %d\n", calculate_lines(file));
    }

    fclose(file);
    exit(EXIT_SUCCESS);
}

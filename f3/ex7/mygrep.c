#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Correct usage: ./mygrep string file.txt\n");
        exit(EXIT_FAILURE);
    }

    char* string = argv[1];
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int line_count = 1;
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *pos = strstr(line, string);
        while (pos != NULL) {
            printf("[%d:%ld]\n", line_count, pos - line);
            pos = strstr(pos + 1, string);
        }
        line_count++;
    }

    exit(EXIT_SUCCESS);
}

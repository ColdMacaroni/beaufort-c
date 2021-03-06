#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "beaufort.h"

void
key_copy(char *source, char **dest);

void
read_until_eof(FILE *source, char **dest, int size);

int
main(int argc, char **argv)
{
    char *key = calloc(sizeof(char), BUFSIZ);
    char *txt = calloc(sizeof(char), BUFSIZ);
    char *dest = calloc(sizeof(char), BUFSIZ);

    // Fill em with 0s
    memset(key, 0, sizeof(char) * BUFSIZ);
    memset(txt, 0, sizeof(char) * BUFSIZ);
    memset(dest, 0, sizeof(char) * BUFSIZ);

    FILE *txt_file = stdin;

    // Check args
    if (argc > 1)
    {
        // If there's a key then load that into the string
        if (strcmp(argv[1], "-k") == 0 || strcmp(argv[1], "--key") == 0)
        {
            if (argc > 2)
                key_copy(argv[2], &key);
            else
            {
                fprintf(stderr, "Please enter a key\n");
                exit(1);
            }
        }

        // If key flag isnt set
        if (key[0] == 0 && argc > 1)
            txt_file = fopen(argv[1], "r");
        // If key flag is set
        else if (key[0] != 0 && argc > 3)
            txt_file = fopen(argv[3], "r");
    }

    // Read from stdin if not given via argument
    if (key[0] == 0)
    {
        char *tmp_key = calloc(sizeof(char), BUFSIZ);

        printf("Enter key: ");
        key_copy(fgets(tmp_key, BUFSIZ, stdin), &key);

        free(tmp_key);
    }

    // Read from stdin if not given via argument
    if (txt_file != NULL)
    {
        if (txt_file == stdin) printf("Enter text. EOF to end input: ");

        read_until_eof(txt_file, &txt, BUFSIZ - 1);
    }

    /* printf("Key: %s\n", key); */
    /* printf("Text: %s\n", txt); */

    beaufort_encode(txt, key, &dest);

    printf("%s", dest);

    if (txt_file != NULL || txt_file != stdin)
        fclose(txt_file);

    free(key);
    free(txt);
    free(dest);

    return 0;
}

void key_copy(char *src, char **dest)
{
    /* Only copy alpha chars (all in upper case) */
    // This is probably very inefficient!
    for (unsigned long i = 0; i < strlen(src); i++)
        if (isalpha(src[i]))
            sprintf(*dest, "%s%c", *dest, _toupper(src[i]));
}

void read_until_eof(FILE *source, char **dest, int size)
{
    /* Read until EOF, past newlines */
    // Temp char for ungetting
    char ch;
    char *tmp = calloc(sizeof(char), BUFSIZ);
    while ((ch = getc(source)) != EOF)
    {
        ungetc(ch, source);

        *dest = strncat(*dest, fgets(tmp, BUFSIZ, source), size - strlen(*dest) - 1);
    }

    free(tmp);
}

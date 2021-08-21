#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
key_copy(char *source, char **dest);

int
main(int argc, char **argv)
{
    char *key = calloc(sizeof(char), BUFSIZ);
    char txt[BUFSIZ];

    // Fill em with 0s
    memset(key, 0, sizeof(char) * BUFSIZ);
    memset(txt, 0, sizeof(char) * BUFSIZ);

    char *current_arg = argv[1];

    // Check args
    if (argc > 1)
    {
        // If there's a key then load that into the string
        if ((strcmp(current_arg, "-k") == 0 || strcmp(current_arg, "--key") == 0) && argc > 2)
        {
            current_arg = argv[2];
            key_copy(current_arg, &key);
        }
    }

    printf("Key: %s\n", key);

    free(key);

    return 0;
}

void key_copy(char *src, char **dest)
{
    for (unsigned long i = 0; i < strlen(src); i++)
        if (isalpha(src[i]))
            sprintf(*dest, "%s%c", *dest, _toupper(src[i]));
}

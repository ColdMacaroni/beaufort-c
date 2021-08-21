#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char
beaufort_encode_chr(char src, char key)
{
    if (!isalpha(src))
        return src;

    // convert letters from ascii to val 0-25
    int ltr = src - (isupper(src) ? 'A' : 'a');
    int key_offset = key - (isupper(key) ? 'A' : 'a');

    // Add the offset
    ltr += key_offset;
    ltr %= 26;

    return (isupper(src) ? 'A' : 'a') + ltr;
}

void
beaufort_encode(char *txt, char *key, char *dest)
{
    unsigned long key_len = strlen(key);
    unsigned long key_i = 0;
    for (unsigned long i = 0; i < strlen(txt); i++)
    {
        // Only do it to alpha chars
        if (isalpha(txt[i]))
            dest[i] = beaufort_encode_chr(txt[i], key[key_i++ % key_len]);
    }
}

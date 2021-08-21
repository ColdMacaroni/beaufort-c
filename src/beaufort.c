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
    key_offset -= ltr;
    if (key_offset < 0) key_offset += 26;

    return (isupper(src) ? 'A' : 'a') + key_offset;
}

void
beaufort_encode(char *txt, char *key, char **dest)
{
    int i = 0;
    int key_len = strlen(key);
    int key_i = 0;

    while (txt[i] != '\0')
    {
        // Only do it to alpha chars
        if (isalpha(txt[i]))
            (*dest)[i] = beaufort_encode_chr(txt[i], key[key_i++ % key_len]);
        else
            (*dest)[i] = txt[i];
        i++;
    }
}

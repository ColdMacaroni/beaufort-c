#include <ctype.h>

char
beaufort_chr(char src, char key)
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

#include <stdio.h>

#define DIGARR "0123456789ABCDEF"

// print a number in any radix
printn (number, radix, file)
int number, radix;
FILE *file;
{
    int i;
    char *digitreps;
    if (number < 0 & radix == 10) {
        fputc ('-', file);
        number = -number;
    }
    if ((i = number / radix) != 0)
        printn (i, radix, file);
    digitreps = DIGARR;
    fputc (digitreps[number % radix], file);
}

#include <ctype.h>
#include <stdio.h>

#include "ir-table.c"

put_name (int c)
{
    int i, l;
    char *n;
    n = codes[c].name;
    l = strlen (n);
    for (i = 0; i < l; i++)
        putchar (tolower (n[i]));
}

main (int argc, char *argv[])
{
    int c, imax;
    char p;

    printf ("// Generated by Small-C's ir2txt.\n");

    // TODO: Remove void entry from codes and
    // update mkir.
    imax = sizeof (codes) / sizeof (struct ircode);
    while (c = getchar ()) {
        c--;
        printf (";%02x\n", c + 1);
        if (c > imax - 1) {
            puts ("ill\n");
            continue;
        }
        put_name (c);
        if (p = codes[c].param)
            putchar (' ');
        switch (p) {
        case 'b':
        case 'w':
        case 'i':
            printf ("%d", getchar () + getchar () << 8);
        case 'l':
            while (c = getchar ())
                putchar (c);
        }
        putchar (10);
    }

    return 0;
}

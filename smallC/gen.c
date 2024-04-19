#include <stdio.h>
#include "defs.h"
#include "data.h"

// return next available internal label number
getlabel ()
{
    return (nxtlab++);
}

// print specified number as label
print_label (int label)
{
    output_label_prefix ();
    output_decimal (label);
}

// glabel - generate label. not used?
glabel (char *lab)
{
    output_string (lab);
    output_label_terminator ();
    newline ();
}

// gnlabel - generate numeric label
generate_label (int nlab)
{
    print_label (nlab);
    output_label_terminator ();
    newline ();
}

// output one byte
output_byte (char c)
{
    if (c == 0)
        return (0);
    fputc (c, output);
    return (c);
}

// output string
output_string (char ptr[])
{
    int k;
    k = 0;
    while (output_byte (ptr[k++]));
}

// outputs tab
print_tab ()
{
    output_byte ('\t');
}

// output line
output_line (char ptr[])
{
    output_with_tab (ptr);
    newline ();
}

// tabbed output
output_with_tab (char ptr[])
{
    print_tab ();
    output_string (ptr);
}

// output decimal number
output_decimal (int number)
{
    fprintf (output, "%d", number);
}

// stores values into memory
store (LVALUE * lval)
{
    if (lval->indirect == 0)
        gen_put_memory (lval->symbol);
    else
        gen_put_indirect (lval->indirect);
}

rvalue (LVALUE * lval, int reg)
{
    if ((lval->symbol != 0) & (lval->indirect == 0))
        gen_get_memory (lval->symbol);
    else
        gen_get_indirect (lval->indirect, reg);
    return HL_REG;
}

// parses test part "(expression)" input and generates assembly for jump
// @param label
// @param ft : false - test jz, true test jnz
test (int label, int ft)
{
    needbrack ("(");
    expression (YES);
    needbrack (")");
    gen_test_jump (label, ft);
}

// scale constant depending on type
scale_const (int type, int otag, int *size)
{
    switch (type) {
    case CINT:
    case UINT:
        *size += *size;
        break;
    case STRUCT:
        *size *= tag_table[otag].size;
        break;
    default:
        break;
    }
}

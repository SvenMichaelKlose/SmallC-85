isalpha (char c)
{
    if ((c >= 'a' & c <= 'z') | (c >= 'A' & c <= 'Z'))
        return (1);
    return (0);
}

isupper (char c)
{
    if (c >= 'A' & c <= 'Z')
        return (1);
    return (0);
}

islower (char c)
{
    if (c >= 'a' & c <= 'z')
        return (1);
    return (0);
}

isdigit (char c)
{
    if (c >= '0' & c <= '9')
        return (1);
    return (0);
}

isspace (char c)
{
    if (c == ' ' | c == '\t' | c == '\n')
        return (1);
    return (0);
}

toupper (char c)
{
    return ((c >= 'a' && c <= 'z') ? c - 32 : c);
}

tolower (char c)
{
    return ((c >= 'A' && c <= 'Z') ? c + 32 : c);
}

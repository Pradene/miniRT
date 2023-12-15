#include "../../includes/rt.h"

int     string_array_size(char **sa)
{
    int i;

    if (!sa)
        return (0);
    i = -1;
    while (sa[++i])
        ;
    return (i);
}

void    string_array_copy(char **dest, char **src)
{
    int i;

    if (!src)
        return ;
    i = -1; 
    while (src[++i])
        dest[i] = src[i];
    dest[i] = NULL;
}

void    string_array_free(char **sa)
{
    int i;

    if (!sa)
        return ;
    i = -1;
    while (sa[++i])
        free(sa[i]);
    free(sa);
    sa = NULL;
}
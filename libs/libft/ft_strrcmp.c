#include "libft.h"

bool    ft_strrcmp(char *s, char *end)
{
    int begin;
    int s_size;
    int end_size;
    int i;

    s_size = ft_strlen(s);
    end_size = ft_strlen(end);
    if (s_size < end_size)
        return (0);
    begin = s_size - end_size;
    if (begin < 0)
        return (0);
    i = 0;
    while (begin + i < s_size)
    {
        if (s[begin + i] != end[i])
            return (0);
        ++i;
    }
    return (1);
}
#include "../../includes/rt.h"

float   ft_atof(char *s, char **end)
{
    float   f;
    int     i;
    float   sign;
    float   factor;

    f = 0.0;
    (*end) = s;
    if (!s)
        return (f);
    sign = 1.0;
    i = 0;
    if (s[i] == '-')
		sign *= -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
    while (ft_isdigit(s[i]))
        f = f * 10 + (s[i++] - '0');
    (*end) = s + i;
    if (s[i] != '.')
        return (f * sign);
    factor = 0.1;
    while (ft_isdigit(s[++i]))
    {
        f += (s[i] - '0') * factor;
        factor /= 10;
    }
    (*end) = s + i;
    return (f * sign);
}
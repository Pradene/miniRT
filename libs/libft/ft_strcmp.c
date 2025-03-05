#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

    i = 0;
	while (s1[i] || s2[i])
	{
		if (((char *)s1)[i] != ((char *)s2)[i])
			return (((char *)s1)[i] - ((char *)s2)[i]);
		i++;
	}
	return (0);
}
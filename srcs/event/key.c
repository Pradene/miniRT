#include "../../includes/rt.h"

int	key(int key, t_data *data)
{
    (void)data;
	printf("%d\n", key);
	if (key == 65307)
		free_data();
	else if (key == 65361)
		return (0);
	else if (key == 65363)
		return (0);
	return (0);
}
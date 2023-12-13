#include "../../includes/rt.h"

// This function define how to interact with the window
void    render()
{
    t_data  *data;

    data = get_data();
    calculate_rays(&data->camera);
    mlx_loop_hook(data->id, &update, data);
	mlx_hook(data->win, 2, 1L << 0, &key, data);
	mlx_hook(data->win, 17, 0, &free_data, data);
    mlx_loop(data->id);
}
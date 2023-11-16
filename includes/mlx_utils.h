#ifndef MLX_UTILS
# define MLX_UTILS

typedef struct s_image
{
	void	*image;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

#endif
RAY		= intersect.c 

OBJECTS = \
	ambient.c \
	camera.c \
	check.c \
	cylinder.c \
	light.c \
	objects.c \
	plane.c \
	sphere.c \

FILES	+= $(addprefix ray/, $(RAY))
FILES	+= $(addprefix objects/, $(OBJECTS))
FILES	+= \
	color.c \
	event.c \
	main.c \
	matrix.c \
	parsing.c \
	point.c \
	render.c \
	scene.c \
	utils.c \
	vector.c \

SRCS	= $(addprefix srcs/, $(FILES))
OBJS	= $(SRCS:srcs/%.c=objs/%.o)
OBJDIR	= objs

CC		= cc
CFLAGS	= -std=c99 -Wall -Wextra -Werror -g -fenable-matrix -Ilibs/mlx_linux -Ilibs/libft -Iincludes
NAME	= minirt

.SILENT:

all: | lft mlx $(NAME)

mlx:
	make -C libs/mlx_linux

lft:
	make -C libs/libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./libs/mlx_linux -lmlx -L./libs/libft -lft -L/usr/lib -lXext -lX11 -lm -lz -fenable-matrix -o $(NAME)

# Fixed compilation rule
objs/%.o: srcs/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	make -C libs/libft clean
	make -C libs/mlx_linux clean

fclean: clean
	rm -f $(NAME)
	make -C libs/libft fclean

re: fclean all

.PHONY: re fclean clean all
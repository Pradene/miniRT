COLOR	= color.c

EVENT	= key.c

MATRICE	= matrice.c

OBJECTS	= camera.c \
		check.c \
		objects.c \
		print.c

PARSING	= parse.c

RAY		= intersect.c

RENDER	= render.c \
		renderer.c

UTILS	= atof.c \
		clamp.c \
		pixel_put.c \
		radian.c \
		string_array.c

VECTOR	= atov4.c \
		cross.c \
		dot.c \
		normalize.c \
		vector.c

FILES	+= $(addprefix color/, $(COLOR))
FILES	+= $(addprefix event/, $(EVENT))
FILES	+= $(addprefix matrice/, $(MATRICE))
FILES	+= $(addprefix objects/, $(OBJECTS))
FILES	+= $(addprefix parsing/, $(PARSING))
FILES	+= $(addprefix ray/, $(RAY))
FILES	+= $(addprefix render/, $(RENDER))
FILES	+= $(addprefix utils/, $(UTILS))
FILES	+= $(addprefix vector/, $(VECTOR))
FILES	+= main.c

SRCS	= $(addprefix srcs/, $(FILES))

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -std=c99 -Wall -Wextra -Werror -g -fenable-matrix

NAME	= minirt

.SILENT:

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: | lft	$(NAME)

lft:
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -L./libft -lft

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean:	clean
	rm -rf $(NAME)
	make -C libft fclean

re:	fclean all

.PHONY: re fclean clean all
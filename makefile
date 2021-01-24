SRC = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ft_cub3d.c ft_draw.c ft_colour.c\
		ft_parce_map.c

all:
	gcc -g -lmlx -framework OpenGL -framework AppKit main.c ./libft/libft.a\
	 $(SRC) libmlx.a

test:
	gcc -g -lmlx -framework OpenGL -framework AppKit ./libft/libft.a $(SRC) libmlx.a test.c 
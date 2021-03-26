NAME := cub3D

SRC := ./gnl/get_next_line.c ./gnl/get_next_line_utils.c  config.c parces.c\
		parce_map.c valid_map.c hook.c ft_draw.c ft_colour.c sprites.c\
		./utils/utils.c sprite_utils.c ft_drawing_sprite.c raycast_utils.c\
		ft_drawing_screen.c ./utils/get_put_pix.c ./utils/free_m.c check_valid_file.c\
		ft_move.c ft_rotate.c getmapheight.c ft_init.c set_mlx_param.c check_param.c\
		screen_shot.c bmp.c main.c ft_res_moves.c

OBJ := $(patsubst %.c, %.o, $(SRC))

CC := gcc -g

FLAGS := -Wall -Wextra -Werror

OPENGL := -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

LIBFT := libft.a

MLX := libmlx.dylib

$(NAME) :		$(MLX) $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ)  $(OPENGL) $(MLX) $(LIBFT) -o $(NAME)

$(MLX) : 
	@$(MAKE) -C mlx
	@mv mlx/$(MLX) .

$(LIBFT) : 
	@$(MAKE) -C libft
	@mv libft/$(LIBFT) .

clean :
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(MLX) $(LIBFT)

re : fclean all

.PHONY:			all clean fclean re

PICS := ./pics/redbricks.xpm ./pics/mossy.xpm ./pics/wood.xpm ./pics/greystone.xpm ./pics/barrel.xpm

test:
	gcc -g -Lmlx -lmlx -framework OpenGL -framework AppKit -lm libft.a libmlx.dylib test.c bmp.c

allcub:
	gcc -g -lmlx -framework OpenGL -framework AppKit  libft.a\
	 $(SRC)  libmlx.dylib

chist:
	rm -rf ~/Library/Caches
	rm -rf ~/Library/Application\ Support/Code/Cache
	rm -rf ~/Library/Application\ Support/Code/CachedData
	rm -rf ~/Library/Application\ Support/Code/CachedExtension
	rm -rf ~/Library/Application\ Support/Code/CachedExtensions
	rm -rf ~/Library/Application\ Support/Code/CachedExtensionVSIXs
	rm -rf ~/Library/Application\ Support/Code/Code\ Cache
	rm -rf ~/Library/Application\ Support/Slack/Cache
	rm -rf ~/Library/Application\ Support/Slack/Code\ Cache
	rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage
	rm -rf ~/Library/Application\ Support/Spotify/PersistentCache
	rm -rf ~/Library/Application\ Support/code/User/workspaceStorage/

add :
	git add $(SRC) cub3d.h $(PICS) map.cub gnl/get_next_line.h makefile

commit:
	git commit -m "mlx"

norm :
	norminette $(SRC) cub3d.h

leak:
	export MallocStackLoggingNoCompact=1

valgrind:
	valgrind --leak-check=yes ./cub3D map.cub
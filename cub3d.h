#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <math.h>

# define PI 3.14159
# define SCALE 16
# define WIDTH 1920
# define HEIGHT 1080
typedef struct		s_point
{
	float			x;
	float			y;
}					t_point;

typedef struct		s_data
{
	void 			*img;
	char 			*addr;
	int 			bits_per_pixel;
	int 			line_length;
	int 			endian;		
	int				colour;
	size_t			res_w;
	size_t			res_h;
} 					t_data;

typedef struct	s_plr
{
	float			x;
	float			y;
	float			plane_x;
	float			plane_y;
	float			alfa;
	float			dir_x;
	float			dir_y;
}					t_plr;

typedef struct		s_vars
{
	void *mlx;
	void *win;
}					t_vars;

typedef struct		s_all
{
	t_data			*win;
	t_plr			*plr;
	t_vars			*vars;
	void			*mlx;
	void			*mlx_win;
	size_t			height;
	char			**map;
}					t_all;

typedef struct		s_color
{
	int	r;
	int	g;
	int	b;
}					t_color;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				ft_cast_ray(t_all *all);
int					key_hook(int keycode, t_all *all);
void				initplr(t_all *all);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					ft_getmapheight();
void				print_map(char **map);
char				**make_map(char **line, int size);
char				*ft_makemap(char **line);
void				gradient(t_data *img, int r, int g, int b);
void				draw_2d_display(t_all *all);
unsigned int		create_trgb(int r, int g, int b);
void				scale_img(t_data *img, int x, int y);
int             	key_hook1(int keycode, t_all *all);
float				Mod(float a);
void				ft_colis(t_all *all);
void				draw3d_display(t_all *all);
void				ft_draw_screen(t_all *all);
void				draw_col(t_all *all, float h, t_plr ray);
void				draw_col1(float x, float h, t_all *all, int color);
void				ft_rounding(double *nmb, int pres);
#endif
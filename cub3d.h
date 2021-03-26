/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:34:27 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/12 19:45:25 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <math.h>

# define PI 3.14159
# define SCALE 8
# define FOV 1.16674602

typedef struct		s_wall_tex
{
	float			wall_x;
	float			step;
	float			tex_pos;
	int				draw_start;
	int				draw_end;
}					t_wall_tex;

typedef struct		s_color
{
	int	r;
	int	g;
	int	b;
}					t_color;

typedef struct		s_sprvals
{
	float			sprite_x;
	float			sprite_y;
	float			inv_det;
	float			trans_x;
	float			trans_y;
	int				sprscreen_x;
	int				spr_h;
	int				spr_w;
	int				stripe;

}					t_sprvals;

typedef struct		s_ray
{
	float			camera_x;
	int				step_x;
	int				step_y;
	float			sidedist_x;
	float			sidedist_y;
	float			deltadist_x;
	float			deltadist_y;
}					t_ray;

typedef struct		s_sprite
{
	float			x;
	float			y;
	float			dist;
	float			angle;
	int				drawstart_x;
	int				drawstart_y;
	int				drawend_x;
	int				drawend_y;
	int				d;
}					t_sprite;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	char			*rel_path;
	int				bpp;
	int				line_length;
	int				endian;
	int				colour;
	int				img_width;
	int				img_height;
	int				tex_x;
	int				tex_y;
	float			wall_x;
}					t_data;

typedef struct		s_nal
{
	int				map;
	int				res;
	int				cel;
	int				fl;
}					t_nal;

typedef struct		s_plr
{
	float			x;
	float			y;
	float			plane_x;
	float			plane_y;
	float			alfa;
	float			dir_x;
	float			dir_y;
	char			start;
}					t_plr;

typedef struct		s_all
{
	t_data			*win;
	t_plr			*plr;
	void			*mlx;
	void			*mlx_win;
	size_t			height;
	char			**map;
	float			raydir_x;
	float			raydir_y;
	int				map_x;
	int				map_y;
	float			pwalldist;
	int				side;
	t_data			texture[5];
	t_sprite		*sprite;
	int				map_width;
	int				map_height;
	float			z_buff[2500];
	t_color			color_f;
	t_color			color_c;
	size_t			max_line;
	int				max_width;
	int				max_height;
	unsigned int	numspr;
	int				save;
	t_nal			nal;
	int				scale;
}					t_all;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				ft_cast_ray(t_all *all);
int					key_hook(int keycode, t_all *all);
void				initplr(t_all *all);
void				print_map(char **map);
void				gradient(t_data *img, int r, int g, int b);
void				draw_2d_display(t_all *all);
unsigned int		create_trgb(int r, int g, int b);
void				scale_img(t_all *all, int x, int y, int color);
void				ft_draw_screen(t_all *all);
void				ft_rounding(double *nmb, int pres);
unsigned int		my_mlx_pixel_get(int line_length, char *addr, int x, int y);
void				ft_draw_tex(t_all *all, float x, float h);
int					ft_texcolor(t_all *all, float h, int i);
void				initexture(t_all *all);
int					init_t(t_all *all);
void				ft_draw_sprites(t_all *all);
void				print(t_sprite *sprite, int num);
void				cell_color(t_all *all);
void				floor_color(t_all *all);
void				parce_res(t_all *all, char *line);
void				parce_tex(t_all *all, char *line);
void				parce_fl_cl(t_all *all, char *line);
void				config_map(t_all *all, char *str, int fd, char *line);
void				print_error(char *str, t_all *all);
int					get_tex_path(char *line, t_all *all, int i);
void				parce_tex_wl(t_all *all, char *line);
char				**ft_make_map(int size, char *str, int max, t_all *all);
int					getmapheight(int fd, char *line, t_all *all);
void				ft_print_map(char **map);
void				valid_map(t_all *all);
void				check_numb_arg(char *line, char ch, int num);
void				ft_initexture(t_all *all);
void				restr_res(t_all *all);
int					make_val(int col);
void				restr_color(t_color *color);
int					move_str(char *line);
void				init_all(t_all *all);
void				config_file(t_all *all, char *str);
void				init_data(t_sprvals *data, t_all *all,
								int i);
void				ft_drawing(t_all *all, t_sprvals *data);
unsigned int		get_numspr(t_all *all);
void				ft_initsprs(t_all *all);
void				ft_distspr(t_all *all);
void				ft_sort(t_all *all);
void				init_plane(t_all *all);
void				calc_dist(t_all *all, t_ray ray);
void				calc_start_val(t_all *all, t_ray *ray, float x);
void				init_dir_sd(t_all *all, t_ray *ray);
int					close_hook(t_all *all);
void				check_valid_file(char *str);
void				clear_all(t_all *all);
void				rotate_r(t_all *all);
void				rotate_l(t_all *all);
void				move_fwrd(t_all *all);
void				move_back(t_all *all);
void				move_right(t_all *all);
void				move_left(t_all *all);
int					getmapheight(int fd, char *line, t_all *all);
void				init_dir(t_all *all);
void				initplr(t_all *all);
void				set_mlx_param(t_all *all);
void				init_sprites(t_all *all);
void				free_m(char **str);
int					check_save(int arc, char **argv, t_all *all);
void				screen_shot(t_all *all);
int					save_bmp(t_all *all);
void				print_error_free(char *str);
void				check_nal(t_all *all);
void				check_double_arg(char *line);
int					check_spaces(char *line);
int					ft_res_move_dig(char *line, int i);
int					ft_res_move_space(char *line, int i);
void				check_max_size(t_all *all, char *line, int i,
									char c);
#endif

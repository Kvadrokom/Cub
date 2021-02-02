/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:07:43 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/02 18:54:57 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

void		rotate(t_all *all, char c)
{
	double	oldplane_x;
	double	olddir_x;
	float	alfa;

	olddir_x = all->plr->dir_x;
	oldplane_x = all->plr->plane_x;
	alfa = 60;
	if (c == 'R')
	{		
		all->plr->dir_x = all->plr->dir_x * cos(-PI / alfa) - all->plr->dir_y * sin(-PI / alfa);
		all->plr->dir_y = olddir_x * sin(-PI / alfa) + all->plr->dir_y * cos(-PI / alfa);
		all->plr->plane_x = all->plr->plane_x * cos(-PI / alfa) - all->plr->plane_y * sin(-PI / alfa);
		all->plr->plane_y = oldplane_x * sin(-PI / alfa) + all->plr->plane_y * cos(-PI / alfa);
	}
	else
	{
		all->plr->dir_x = all->plr->dir_x * cos(PI / alfa) - all->plr->dir_y * sin(PI / alfa);
		all->plr->dir_y = olddir_x * sin(PI / alfa) + all->plr->dir_y * cos(PI / alfa);
		all->plr->plane_x = all->plr->plane_x * cos(PI / alfa) - all->plr->plane_y * sin(PI / alfa);
		all->plr->plane_y = oldplane_x * sin(PI / alfa) + all->plr->plane_y * cos(PI / alfa);
	}	
}

int			key_hook(int keycode, t_all *all)
{
	mlx_clear_window(all->vars->mlx, all->vars->win);
	if (keycode == 126 || keycode == 13)
    {
		if (all->map[(int)(all->plr->y + all->plr->dir_y)][(int)all->plr->x] != '1')
			all->plr->y += all->plr->dir_y / 8;
		if (all->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir_x)] != '1')
			all->plr->x += all->plr->dir_x / 8;
	}
    if (keycode == 125 || keycode == 1)
    {
		if (all->map[(int)(all->plr->y - all->plr->dir_y)][(int)all->plr->x] != '1')
			all->plr->y -= all->plr->dir_y / 8;
		if (all->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir_x)] != '1')
			all->plr->x -= all->plr->dir_x / 8;
	}
    if (keycode == 124 || keycode == 2)
		rotate(all, 'R');
	if (keycode == 123 || keycode == 0)
		rotate(all, 'L');
	ft_draw_screen(all);
    return (0);
}

void	init_plane(t_all *all)
{
	if (all->plr->dir_x == 0)
	{
		all->plr->plane_x = (all->plr->dir_y > 0) ? .66 : -.66;
		all->plr->plane_y = 0;
	}
	else if (all->plr->dir_y == 0)
	{
		all->plr->plane_y = (all->plr->dir_x > 0) ? -.66 : .66;
		all->plr->plane_x = 0;
	}
}

unsigned int my_mlx_pixel_get(int line_length, char *addr, int x, int y, int bpp)
{
	return (*(unsigned int *)(addr + y * line_length + x * bpp / 8));
}

void	ft_draw_screen(t_all *all)
{
	float	x;
	float	camera_x;
	int		step_x;
	int		step_y;
	int		hit;
	float	sidedist_x;
	float	sidedist_y;
	float	deltadist_x;
	float	deltadist_y;
	t_data	*img;
	t_color color;
	t_plr	ray;

	init_plane(all);
	x = 0;
	img = all->win;
	img->img = mlx_new_image(all->vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
								  &img->endian);
	gradient(img, color.r, color.g, color.b);
	while (x < WIDTH)
	{
		camera_x = 2 * x / WIDTH - 1;
		hit = 0;
		all->raydir_x = all->plr->dir_x + all->plr->plane_x * camera_x;
		all->raydir_y = all->plr->dir_y + all->plr->plane_y * camera_x;
		all->map_x = (int)all->plr->x;
		all->map_y = (int)all->plr->y;
		deltadist_x = (all->raydir_y == 0) ? 0 : ((all->raydir_x == 0) ? 1 : fabs(1 / all->raydir_x));
		deltadist_y = (all->raydir_x == 0) ? 0 : ((all->raydir_y == 0) ? 1 : fabs(1 / all->raydir_y));
		if (all->raydir_x < 0)
		{
			step_x = -1;
			sidedist_x = (all->plr->x - all->map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (-all->plr->x + 1 + all->map_x) * deltadist_x;
		}
		if (all->raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (all->plr->y - all->map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (-all->plr->y + 1 + all->map_y) * deltadist_y;
		}
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				all->map_x += step_x;
				all->side = 0;
			}
			else
			{
				sidedist_y += deltadist_y;
				all->map_y += step_y;
				all->side = 1;
			}
			if (all->map[all->map_y][all->map_x] == '1')
				hit = 1;
		}
		if (!all->side)
		{
			all->pwalldist = (all->map_x - all->plr->x + (1 - step_x) / 2) / all->raydir_x;
			color.r = 0x0099ff;
		}
		else
		{
			all->pwalldist = (all->map_y - all->plr->y + (1 - step_y) / 2) / all->raydir_y;
			color.r = 0x0099ff / 2;
		}
		//draw_col1(x, HEIGHT / all->pwalldist, all, color.r);
		all->z_buff[(int)x] = all->pwalldist;
		ft_draw_tex(all, x, HEIGHT / all->pwalldist);
		x++;
	}
	//draw_2d_display(all);
	ft_draw_sprites(all);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, img->img, 0, 0);
	mlx_destroy_image(all->vars->mlx, img->img);
}
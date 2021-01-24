/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:07:43 by skharjo           #+#    #+#             */
/*   Updated: 2021/01/24 08:20:10 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void		rotate(t_all *all, char c)
{
	double	oldplane_y;
	double	olddir_y;

	olddir_y = all->plr->dir_y;
	oldplane_y = all->plr->plane_y;
	if (c == 'R')
	{		
		all->plr->dir_y = all->plr->dir_y * cos(-PI / 90) - all->plr->dir_x * sin(-PI / 90);
		all->plr->dir_x = olddir_y * sin(-PI / 90) + all->plr->dir_x * cos(-PI / 90);
		all->plr->plane_y = all->plr->plane_y * cos(-PI / 90) - all->plr->plane_x * sin(-PI / 90);
		all->plr->plane_x = oldplane_y * sin(-PI / 90) + all->plr->plane_x * cos(-PI / 90);
	}
	else
	{
		all->plr->dir_y = all->plr->dir_y * cos(PI / 90) - all->plr->dir_x * sin(PI / 90);
		all->plr->dir_x = olddir_y * sin(PI / 90) + all->plr->dir_x * cos(PI / 90);
		all->plr->plane_y = all->plr->plane_y * cos(PI / 90) - all->plr->plane_x * sin(PI / 90);
		all->plr->plane_x = oldplane_y * sin(PI / 90) + all->plr->plane_x * cos(PI / 90);
	}	
}

int			key_hook(int keycode, t_all *all)
{
	mlx_clear_window(all->vars->mlx, all->vars->win);
	if (keycode == 126 || keycode == 13)
    {
		if (all->map[(int)(all->plr->y + all->plr->dir_y)][(int)all->plr->x] == '0')
			all->plr->y += all->plr->dir_y;
		if (all->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir_x)] == '0')
			all->plr->x += all->plr->dir_x;
	}
    if (keycode == 125 || keycode == 1)
    {
		if(all->map[(int)(all->plr->y - all->plr->dir_y)][(int)all->plr->x] == '0')
			all->plr->y -= all->plr->dir_y;
		if (all->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir_x)] == '0')
			all->plr->x -= all->plr->dir_x;
	}
    if (keycode == 124 || keycode == 2)
		rotate(all, 'R');
	if (keycode == 123 || keycode == 0)
		rotate(all, 'L');
	ft_draw_screen(all);
    return (0);
}

void	ft_draw_screen(t_all *all)
{
	float	x;
	float	camera_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	float	raydir_x;
	float	raydir_y;
	float	sidedist_x;
	float	sidedist_y;
	float	deltadist_x;
	float	deltadist_y;
	float	pwalldist;
	t_data	*img;
	t_color color;
	t_plr	ray;

	all->plr->plane_x = 0;
	all->plr->plane_y = .66;
	x = 0;
	img = all->win;
	img->img = mlx_new_image(all->vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								  &img->endian);
	gradient(img, color.r, color.g, color.b);
	while (x < WIDTH)
	{
		camera_x = 2 * x / WIDTH - 1;
		hit = 0;
		raydir_x = all->plr->dir_x + all->plr->plane_x * camera_x;
		raydir_y = all->plr->dir_y + all->plr->plane_y * camera_x;
		map_x = (int)all->plr->x;
		map_y = (int)all->plr->y;
		deltadist_x = (raydir_y == 0) ? 0 : ((raydir_x == 0) ? 1 : fabs(1 / raydir_x));
		deltadist_y = (raydir_x == 0) ? 0 : ((raydir_y == 0) ? 1 : fabs(1 / raydir_y));
		if (raydir_x < 0)
		{
			step_x = -1;
			sidedist_x = (all->plr->x - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (all->plr->x + 1 - map_x) * deltadist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (all->plr->y - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (all->plr->y + 1 - map_y) * deltadist_y;
		}
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				sidedist_y += deltadist_y;
				map_y += step_y;
				side = 1;
			}
			if (all->map[map_y][map_x] != '0')
				hit = 1;
		}
		if (!side)
		{
			pwalldist = (map_x - all->plr->x + (1 - step_x) / 2) / raydir_x;
			color.r = 0x0099ff;
		}
		else
		{
			pwalldist = (map_y - all->plr->y + (1 - step_y) / 2) / raydir_y;
			color.r = 0xffff00;
		}
		draw_col1(x, HEIGHT / pwalldist, all, color.r);
		x++;
	}
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, img->img, 0, 0);
	mlx_destroy_image(all->vars->mlx, img->img);
}
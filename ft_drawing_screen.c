/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:03:31 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/01 17:54:01 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_all *all, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			all->map_x += ray->step_x;
			all->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			all->map_y += ray->step_y;
			all->side = 1;
		}
		if (all->map[all->map_y][all->map_x] == '1')
			hit = 1;
	}
}

void	ft_draw_screen(t_all *all)
{
	float	x;
	t_ray	ray;

	init_plane(all);
	x = 0;
	all->win->img = mlx_new_image(all->mlx, all->map_width, all->map_height);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
					&all->win->line_length, &all->win->endian);
	floor_color(all);
	cell_color(all);
	while (x < all->map_width)
	{
		calc_start_val(all, &ray, x);
		init_dir_sd(all, &ray);
		raycast(all, &ray);
		calc_dist(all, ray);
		all->z_buff[(int)x] = all->pwalldist;
		ft_draw_tex(all, x, all->map_height / all->pwalldist);
		x++;
	}
	ft_draw_sprites(all);
	screen_shot(all);
	draw_2d_display(all);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->win->img, 0, 0);
	mlx_destroy_image(all->mlx, all->win->img);
}

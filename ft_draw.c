/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:48:08 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/12 20:21:18 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wall_tex(t_all *all, t_wall_tex *data, int t, float h)
{
	if (all->side == 0)
		data->wall_x = all->plr->y + all->raydir_y * all->pwalldist;
	else
		data->wall_x = all->plr->x + all->raydir_x * all->pwalldist;
	data->wall_x -= (int)data->wall_x;
	all->texture[t].tex_x = (int)(data->wall_x
							* (float)(all->texture[t].img_width));
	if ((all->side == 0 && all->raydir_x > 0) ||
		(all->side == 1 && all->raydir_y < 0))
		all->texture[t].tex_x = all->texture[t].img_width -
								all->texture[t].tex_x - 1;
	data->step = 1 * all->texture[t].img_height / h;
	data->draw_start = -h / 2 + all->map_height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = h / 2 + all->map_height / 2;
	if (data->draw_end >= all->map_height)
		data->draw_end = all->map_height - 1;
}

void	ft_draw_tex(t_all *all, float x, float h)
{
	int			t;
	int			color;
	t_wall_tex	data;

	t = init_t(all);
	init_wall_tex(all, &data, t, h);
	while (data.draw_start < data.draw_end)
	{
		data.tex_pos = (data.draw_start + h / 2 -
						all->map_height / 2) * data.step;
		all->texture[t].tex_y = (int)data.tex_pos &
								(all->texture[t].img_height - 1);
		data.tex_pos += data.step;
		color = my_mlx_pixel_get(all->texture[t].line_length,
				all->texture[t].addr,
				all->texture[t].tex_x, all->texture[t].tex_y);
		my_mlx_pixel_put(all->win, x, data.draw_start, color);
		data.draw_start++;
	}
}

void	scale_img(t_all *all, int x, int y, int color)
{
	int		i;
	int		j;
	float	cx;
	float	cy;

	i = 0;
	while (i < all->scale)
	{
		j = 0;
		while (j < all->scale)
		{
			cx = x + j;
			cy = y + i;
			if (cx < all->map_width && cy < all->map_height)
				my_mlx_pixel_put(all->win, cx, cy, color);
			j++;
		}
		i++;
	}
}

void	draw_2d_display(t_all *all)
{
	size_t 	i;
	size_t 	j;
	int		scale;

	i = 0;
	all->scale = (all->map_width + all->map_height) / 250;
	scale = all->scale;
	while (i < all->height)
	{
		j = 0;
		while (j < ft_strlen(all->map[i]))
		{
			if ((all->map)[i][j] == '1')
				scale_img(all, j * scale, i * scale, 0xffffff);
			j++;
		}
		i++;
	}
	scale_img(all, all->plr->x * scale, all->plr->y * scale, 0x990099);
}

int		init_t(t_all *all)
{
	int t;

	t = 0;
	if (all->side == 0)
	{
		if (all->raydir_x > 0)
			t = 1;
		else if (all->raydir_x < 0)
			t = 2;
	}
	else if ((all->side) == 1)
	{
		if (all->raydir_y > 0)
			t = 3;
		else if (all->raydir_y < 0)
			t = 0;
	}
	return (t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:41:52 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/27 16:06:00 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void			init_vals(t_data *val, t_all *all, int t)
{
	if (all->side == 0)
	{
		val->wall_x = all->plr->y + all->raydir_y * all->pwalldist;
		val->tex_x = abs((int)((val->wall_x - (int)val->wall_x) *
					all->texture[t].img_width));
	}
	else
	{
		val->wall_x = all->plr->x + all->raydir_x * all->pwalldist;
		val->tex_x = abs((int)(((int)val->wall_x - val->wall_x) *
								all->texture[t].img_width));
	}
}

int				ft_texcolor(t_all *all, float h, int i)
{
	int		color;
	t_data	val;
	int		t;

	t = init_t(all);
	init_vals(&val, all, t);
	if ((all->side == 0 && all->raydir_x > 0) || (all->side == 1 &&
		all->raydir_y < 0))
		val.tex_x = all->texture[1].img_width - val.tex_x - 1;
	val.tex_y = (int)(i * (all->texture[t].img_height - 1) / (h - 1));
	color = my_mlx_pixel_get(all->texture[t].line_length,
			all->texture[t].addr,
			val.tex_x, val.tex_y);
	if (all->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

void			cell_color(t_all *all)
{
	float	x;
	float	y;
	int		fcol;

	x = 0;
	fcol = create_trgb(all->color_c.r, all->color_c.g, all->color_c.b);
	while (x < all->map_width)
	{
		y = all->map_height / 2;
		while (y >= 0)
		{
			my_mlx_pixel_put(all->win, x, y, fcol);
			y--;
		}
		x++;
	}
}

void			floor_color(t_all *all)
{
	float	x;
	float	y;
	int		fcel;

	x = 0;
	fcel = create_trgb(all->color_f.r, all->color_f.g, all->color_f.b);
	while (x < all->map_width)
	{
		y = all->map_height / 2;
		while (y < all->map_height)
		{
			my_mlx_pixel_put(all->win, x, y, fcel);
			y++;
		}
		x++;
	}
}

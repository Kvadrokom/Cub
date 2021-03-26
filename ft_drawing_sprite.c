/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:56:08 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/27 20:15:40 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_start_pos(t_sprite *sprite, t_all *all, t_sprvals *data)
{
	sprite->drawend_y = data->spr_h / 2 + all->map_height / 2;
	sprite->drawend_y = sprite->drawend_y >= all->map_height ?
						all->map_height - 1 : sprite->drawend_y;
	sprite->drawstart_x = data->sprscreen_x - data->spr_w / 2;
	sprite->drawstart_x = sprite->drawstart_x < 0 ? 0 : sprite->drawstart_x;
	sprite->drawend_x = data->sprscreen_x + data->spr_w / 2;
	sprite->drawend_x = sprite->drawend_x >= all->map_width ?
						all->map_width - 1 : sprite->drawend_x;
}

void	draw_sprite(t_all *all, int stripe, t_sprvals *data)
{
	int color;

	while (all->sprite->drawstart_y < all->sprite->drawend_y)
	{
		all->sprite->d = all->sprite->drawstart_y * 256 -
						all->map_height * 128 + data->spr_h * 128;
		all->texture[4].tex_y = ((all->sprite->d * all->texture[4].img_height)
								/ data->spr_h) / 256;
		color = my_mlx_pixel_get(all->texture[4].line_length,
								all->texture[4].addr,
								all->texture[4].tex_x, all->texture[4].tex_y);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(all->win, (float)stripe,
							(float)all->sprite->drawstart_y, color);
		all->sprite->drawstart_y++;
	}
}

void	ft_drawing(t_all *all, t_sprvals *data)
{
	int stripe;

	set_start_pos(all->sprite, all, data);
	stripe = all->sprite->drawstart_x;
	while (stripe < all->sprite->drawend_x)
	{
		all->texture[4].tex_x = (int)(256 * (stripe -
								(-data->spr_w / 2. + data->sprscreen_x))
								* all->texture[4].img_width / data->spr_w)
								/ 256;
		all->sprite->drawstart_y = -data->spr_h / 2 + all->map_height / 2;
		all->sprite->drawstart_y = (all->sprite->drawstart_y < 0) ? 0 :
									all->sprite->drawstart_y;
		if (data->trans_y > 0 && stripe > 0 &&
			stripe < all->map_width &&
			data->trans_y < all->z_buff[stripe])
			draw_sprite(all, stripe, data);
		stripe++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:18:40 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/05 19:13:32 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_sprvals *data, t_all *all, int i)
{
	data->sprite_x = all->sprite[i].x - all->plr->x;
	data->sprite_y = all->sprite[i].y - all->plr->y;
	data->inv_det = 1.0 / (all->plr->plane_x * all->plr->dir_y -
							all->plr->dir_x * all->plr->plane_y);
	data->trans_x = data->inv_det * (-all->plr->dir_y * data->sprite_x +
										all->plr->dir_x * data->sprite_y);
	data->trans_y = data->inv_det * (-all->plr->plane_y * data->sprite_x +
					all->plr->plane_x * data->sprite_y);
	data->sprscreen_x = (int)(all->map_width / 2 *
						(1 + data->trans_x / data->trans_y));
	data->spr_h = abs((int)(all->map_height / data->trans_y));
	data->spr_w = abs((int)(all->map_height / data->trans_y));
}

void	ft_draw_sprites(t_all *all)
{
	unsigned int	i;
	t_sprvals		data;

	i = 0;
	if (all->numspr)
	{
		ft_distspr(all);
		ft_sort(all);
		while (i < all->numspr)
		{
			init_data(&data, all, i);
			ft_drawing(all, &data);
			i++;
		}
	}
}

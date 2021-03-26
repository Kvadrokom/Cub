/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:10:13 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/27 20:29:44 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_fwrd(t_all *all)
{
	char	c;

	c = all->map[(int)(all->plr->y + all->plr->dir_y / 2)][(int)all->plr->x];
	if (c != '1' && c != '2')
		all->plr->y += all->plr->dir_y / 4;
	c = all->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir_x / 2)];
	if (c != '1' && c != '2')
		all->plr->x += all->plr->dir_x / 4;
}

void	move_back(t_all *all)
{
	char	c;

	c = all->map[(int)(all->plr->y - all->plr->dir_y / 2)][(int)all->plr->x];
	if (c != '1' && c != '2')
		all->plr->y -= all->plr->dir_y / 4;
	c = all->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir_x / 2)];
	if (c != '1' && c != '2')
		all->plr->x -= all->plr->dir_x / 4;
}

void	move_right(t_all *all)
{
	char c;

	c = all->map[(int)(all->plr->y)][(int)(all->plr->x - all->plr->dir_y / 4)];
	if (c != '1' && c != '2')
		all->plr->x -= all->plr->dir_y / 8;
	c = all->map[(int)(all->plr->y + all->plr->dir_x / 4)][(int)all->plr->x];
	if (c != '1' && c != '2')
		all->plr->y += all->plr->dir_x / 8;
}

void	move_left(t_all *all)
{
	char	c;

	c = all->map[(int)(all->plr->y)][(int)(all->plr->x + all->plr->dir_y / 4)];
	if (c != '1' && c != '2')
		all->plr->x += all->plr->dir_y / 8;
	c = all->map[(int)(all->plr->y - all->plr->dir_x / 4)][(int)all->plr->x];
	if (c != '1' && c != '2')
		all->plr->y -= all->plr->dir_x / 8;
}

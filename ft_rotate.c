/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:13:30 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/27 20:25:11 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_l(t_all *all)
{
	double	oldplane_x;
	double	olddir_x;
	float	alfa;

	olddir_x = all->plr->dir_x;
	oldplane_x = all->plr->plane_x;
	alfa = 15;
	all->plr->dir_x = all->plr->dir_x * cos(-PI / alfa) -
					all->plr->dir_y * sin(-PI / alfa);
	all->plr->dir_y = olddir_x * sin(-PI / alfa) +
					all->plr->dir_y * cos(-PI / alfa);
	all->plr->plane_x = all->plr->plane_x * cos(-PI / alfa) -
					all->plr->plane_y * sin(-PI / alfa);
	all->plr->plane_y = oldplane_x * sin(-PI / alfa) +
					all->plr->plane_y * cos(-PI / alfa);
	all->plr->alfa = atan2(all->plr->dir_y, all->plr->dir_x);
}

void	rotate_r(t_all *all)
{
	double	oldplane_x;
	double	olddir_x;
	float	alfa;

	olddir_x = all->plr->dir_x;
	oldplane_x = all->plr->plane_x;
	alfa = 15;
	all->plr->dir_x = all->plr->dir_x * cos(PI / alfa) -
					all->plr->dir_y * sin(PI / alfa);
	all->plr->dir_y = olddir_x * sin(PI / alfa) +
					all->plr->dir_y * cos(PI / alfa);
	all->plr->plane_x = all->plr->plane_x * cos(PI / alfa) -
					all->plr->plane_y * sin(PI / alfa);
	all->plr->plane_y = oldplane_x * sin(PI / alfa) +
					all->plr->plane_y * cos(PI / alfa);
	all->plr->alfa = atan2(all->plr->dir_y, all->plr->dir_x);
}

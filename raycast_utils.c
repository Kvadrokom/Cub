/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:07:31 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/26 21:36:57 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	calc_dist(t_all *all, t_ray ray)
{
	if (!all->side)
		all->pwalldist = (all->map_x - all->plr->x + (1. - ray.step_x) / 2.)
						/ all->raydir_x;
	else
		all->pwalldist = (all->map_y - all->plr->y + (1. - ray.step_y) / 2.)
						/ all->raydir_y;
}

void	calc_start_val(t_all *all, t_ray *ray, float x)
{
	ray->camera_x = 1 - 2 * x / all->map_width;
	all->raydir_x = all->plr->dir_x + all->plr->plane_x * ray->camera_x;
	all->raydir_y = all->plr->dir_y + all->plr->plane_y * ray->camera_x;
	all->map_x = (int)all->plr->x;
	all->map_y = (int)all->plr->y;
	if (all->raydir_y == 0)
		ray->deltadist_x = 0;
	else if (all->raydir_x == 0)
		ray->deltadist_x = 1;
	else
		ray->deltadist_x = fabs(1 / all->raydir_x);
	if (all->raydir_x == 0)
		ray->deltadist_y = 0;
	else if (all->raydir_y == 0)
		ray->deltadist_y = 1;
	else
		ray->deltadist_y = fabs(1 / all->raydir_y);
}

void	init_dir_sd(t_all *all, t_ray *ray)
{
	if (all->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (all->plr->x - all->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (-all->plr->x + 1 + all->map_x) * ray->deltadist_x;
	}
	if (all->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (all->plr->y - all->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (-all->plr->y + 1 + all->map_y) * ray->deltadist_y;
	}
}

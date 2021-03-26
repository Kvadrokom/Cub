/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:07:43 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/28 19:03:32 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_hook(int keycode, t_all *all)
{
	if (keycode == 126 || keycode == 13)
		move_fwrd(all);
	if (keycode == 125 || keycode == 1)
		move_back(all);
	if (keycode == 2)
		rotate_r(all);
	if (keycode == 0)
		rotate_l(all);
	if (keycode == 124)
		move_right(all);
	if (keycode == 123)
		move_left(all);
	if (keycode == 53)
	{
		mlx_destroy_window(all->mlx, all->mlx_win);
		clear_all(all);
		exit(EXIT_FAILURE);
	}
	ft_draw_screen(all);
	return (0);
}

int		close_hook(t_all *all)
{
	mlx_destroy_window(all->mlx, all->mlx_win);
	clear_all(all);
	exit(EXIT_SUCCESS);
}

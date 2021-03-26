/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:45:11 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/28 15:15:54 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mlx_param(t_all *all)
{
	if (!(all->mlx = mlx_init()))
		print_error("mlx error", all);
	if (!(all->mlx_win = mlx_new_window(all->mlx, all->map_width,
		all->map_height, "Cub3d")))
		print_error("mlx error", all);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:56:10 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/02 20:13:08 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screen_shot(t_all *all)
{
	if (all->save)
	{
		if (!save_bmp(all))
			print_error("Can't save image", all);
		else
			mlx_destroy_window(all->mlx, all->mlx_win);
		clear_all(all);
		exit(EXIT_SUCCESS);
	}
}

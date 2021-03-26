/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:27:51 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/28 14:57:45 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir(t_all *all)
{
	if (all->plr->start == 'N')
	{
		all->plr->dir_x = 0;
		all->plr->dir_y = -1;
		all->plr->alfa = 3 * PI / 2;
	}
	else if (all->plr->start == 'W')
	{
		all->plr->dir_x = -1;
		all->plr->dir_y = 0;
		all->plr->alfa = PI;
	}
	else if (all->plr->start == 'S')
	{
		all->plr->dir_x = 0;
		all->plr->dir_y = 1;
		all->plr->alfa = PI / 2;
	}
	else
	{
		all->plr->dir_x = 1;
		all->plr->dir_y = 0;
		all->plr->alfa = 0;
	}
}

void	initplr(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (ft_strchr("NSWE", all->map[i][j]))
			{
				all->plr->x = j + .5;
				all->plr->y = i + .5;
				all->plr->start = *(ft_strchr("NSWE", all->map[i][j]));
			}
			j++;
		}
		i++;
	}
	init_dir(all);
}

void	ft_initexture(t_all *all)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		all->texture[i].img = mlx_xpm_file_to_image(
			all->mlx, all->texture[i].rel_path, &all->texture[i].img_width,
		&all->texture[i].img_height);
		if (!(all->texture[i].img))
			print_error("Wrong texture path or mlx error", all);
		all->texture[i].addr = mlx_get_data_addr(
			all->texture[i].img, &all->texture[i].bpp,
			&all->texture[i].line_length, &all->texture[i].endian);
		i++;
	}
}

void	init_sprites(t_all *all)
{
	all->numspr = get_numspr(all);
	if (all->numspr == 0)
		return ;
	if ((all->sprite = malloc(sizeof(t_sprite) * all->numspr)) == NULL)
		print_error("Bad malloc allocation", all);
	ft_initsprs(all);
}

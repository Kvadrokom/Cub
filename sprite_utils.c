/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:56:16 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/27 20:13:33 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_numspr(t_all *all)
{
	unsigned int	num;
	int				i;
	int				j;

	i = 0;
	j = 0;
	num = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
				num++;
			j++;
		}
		i++;
	}
	return (num);
}

void			ft_initsprs(t_all *all)
{
	int			i;
	int			j;
	int			z;

	i = 0;
	z = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				all->sprite[z].x = j + .5;
				all->sprite[z].y = i + .5;
				z++;
			}
			j++;
		}
		i++;
	}
}

void			ft_distspr(t_all *all)
{
	unsigned int	i;

	i = 0;
	while (i < all->numspr)
	{
		all->sprite[i].dist = (all->plr->x - all->sprite[i].x) *
							(all->plr->x - all->sprite[i].x) +
							(all->plr->y - all->sprite[i].y) *
							(all->plr->y - all->sprite[i].y);
		i++;
	}
}

void			ft_sort(t_all *all)
{
	unsigned int	i;
	unsigned int	j;
	int				noswap;
	t_sprite		tmp;

	i = all->numspr - 1;
	while (i >= 0)
	{
		j = 0;
		noswap = 0;
		while (j < i)
		{
			if (all->sprite[j].dist < all->sprite[j + 1].dist)
			{
				tmp = all->sprite[j];
				all->sprite[j] = all->sprite[j + 1];
				all->sprite[j + 1] = tmp;
				noswap = 1;
			}
			j++;
		}
		if (noswap == 0)
			break ;
		i--;
	}
}

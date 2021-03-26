/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:07:22 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/12 20:09:05 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_plr(t_all *all)
{
	size_t	i;
	size_t	j;
	int		count;
	size_t	k;

	i = 0;
	count = 0;
	while (i < all->height)
	{
		j = 0;
		k = ft_strlen(all->map[i]);
		while (j < k)
		{
			if (ft_strchr("NSEW", all->map[i][j]))
				count++;
			if (!ft_strchr("120NSEW ", all->map[i][j]))
				print_error("Wrong map format", all);
			j++;
		}
		i++;
	}
	if (count != 1)
		print_error("Wrong map format", all);
}

int		check_bdr(char **map, size_t i, size_t j)
{
	if (map[i + 1][j] == ' ' || map[i][j + 1] == ' '
		|| map[i - 1][j] == ' ' || map[i][j - 1] == ' '
		|| map[i + 1][j] == '\0' || map[i][j + 1] == '\0'
		|| map[i - 1][j] == '\0' || map[i][j - 1] == '\0')
		return (0);
	return (1);
}

void	check_map_bdr(t_all *all)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	while (i < all->height)
	{
		j = 0;
		k = ft_strlen(all->map[i]);
		while (j < k)
		{
			if (ft_strchr("NSEW20", all->map[i][j]))
			{
				if (j == k - 1 || i == 0 || j == 0
					|| i == all->height - 1)
					print_error("Wrong map format", all);
				if (!check_bdr(all->map, i, j))
					print_error("Wrong map format", all);
			}
			j++;
		}
		i++;
	}
}

void	valid_map(t_all *all)
{
	static int count;

	count++;
	if (count > 1)
		print_error("Duplicate lines", all);
	check_map_plr(all);
	check_map_bdr(all);
}

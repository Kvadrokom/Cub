/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_res_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:12:16 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/09 20:53:49 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_res_move_dig(char *line, int i)
{
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int		ft_res_move_space(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

void	check_max_size(t_all *all, char *line, int i, char c)
{
	int count;

	count = 0;
	while (line[i] == '0')
		i++;
	while (ft_isdigit(line[i]))
	{
		count++;
		i++;
	}
	if (count > 4)
	{
		if (c == 'w')
			all->map_width = 5000;
		else if (c == 'h')
			all->map_height = 5000;
	}
}

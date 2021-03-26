/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmapheight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:23:00 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/28 17:24:45 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		getmapheight(int fd, char *line, t_all *all)
{
	int	i;

	i = 1;
	all->max_line = ft_strlen(line);
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		if (line)
		{
			if (all->max_line < ft_strlen(line))
				all->max_line = ft_strlen(line);
			i++;
			free(line);
		}
		else
			print_error("Bad malloc allocation", all);
	}
	free(line);
	i++;
	close(fd);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 21:12:26 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/28 18:17:13 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map_line(char *str, char *line)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(line))
	{
		str[i] = line[i];
		i++;
	}
	free(line);
	return (str);
}

char	*move_to_map(int fd, char *line, t_all *all)
{
	while (get_next_line(fd, &line) && ft_atoi(line) == 0)
	{
		if (line)
			free(line);
		else
			print_error("Bad malloc allocation", all);
	}
	return (line);
}

char	**fill_map(char **map, t_all *all, char *str)
{
	int				i;
	int				fd;
	static char		*line;

	i = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	map_line(map[i], move_to_map(fd, line, all));
	i++;
	while (get_next_line(fd, &line))
	{
		if (!line)
			print_error("Bad malloc allocation", all);
		map_line(map[i], line);
		i++;
	}
	map_line(map[i], line);
	i++;
	map[i] = 0;
	close(fd);
	return (map);
}

char	**ft_make_map(int size, char *str, int max, t_all *all)
{
	char	**map;
	int		i;

	i = 0;
	if (!(map = (char **)malloc(sizeof(char *) * (size + 1))))
		print_error("Bad malloc allocation", all);
	while (i < size)
	{
		if (!(map[i++] = (char *)ft_calloc(sizeof(char), (max + 1))))
			print_error("Bad malloc allocation", all);
	}
	map = fill_map(map, all, str);
	return (map);
}

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	if (map == 0)
		return ;
	while (map[i])
		ft_putendl_fd(map[i++], 1);
}

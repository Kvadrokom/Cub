/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 20:32:43 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/05 20:25:36 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_numb_arg(char *line, char ch, int num)
{
	char	**str;
	int		count;
	int		i;

	str = ft_split(line, ch);
	i = 0;
	count = 0;
	if (str == NULL)
		print_error_free("Bad malloc allocation");
	while (str[i++])
		count++;
	if (count != num)
		print_error_free("Wrong number arguments");
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	config_lines(char *line, t_all *all)
{
	if (ft_strchr("R", *line))
	{
		all->nal.res = 1;
		check_numb_arg(line, ' ', 3);
		parce_res(all, line);
	}
	else if (!ft_strncmp("NO", line, 2) || !ft_strncmp("SO", line, 2)
			|| !ft_strncmp("EA", line, 2) || !ft_strncmp("WE", line, 2))
		parce_tex_wl(all, line);
	else if (!ft_strncmp("S", line, 1))
	{
		if (!get_tex_path(line, all, 4))
			print_error_free("Wrong texture format");
	}
	else if (ft_strchr("FC", *line))
	{
		all->nal.cel = (*line == 'F') ? 1 : all->nal.cel;
		all->nal.fl = (*line == 'C') ? 1 : all->nal.fl;
		parce_fl_cl(all, line);
	}
	else
		print_error_free("Wrong map format");
}

void	config_map(t_all *all, char *str, int fd, char *line)
{
	all->height = getmapheight(fd, line, all);
	if (!(all->map = ft_make_map(all->height, str, all->max_line, all)))
		print_error("Bad malloc allocation", all);
	valid_map(all);
}

void	config_file(t_all *all, char *str)
{
	int		fd;
	char	*line;

	if ((fd = open(str, O_RDWR)) < 0)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line))
	{
		if (!line)
			print_error("Bad malloc allocation", all);
		if (!ft_strchr("\0", *line) && ft_atoi(line) == 0
			&& check_spaces(line))
			config_lines(line, all);
		else if (ft_atoi(line) != 0)
		{
			all->nal.map = 1;
			config_map(all, str, fd, line);
			return ;
		}
		free(line);
	}
	free(line);
	close(fd);
}

void	init_all(t_all *all)
{
	all->map = 0;
	all->map_height = 0;
	all->map_width = 0;
	all->map_x = 0;
	all->map_y = 0;
	all->max_line = 0;
	all->mlx = 0;
	all->mlx_win = 0;
	all->plr = 0;
	all->sprite = 0;
	all->win = 0;
	all->texture[0].rel_path = NULL;
	all->texture[1].rel_path = NULL;
	all->texture[2].rel_path = NULL;
	all->texture[3].rel_path = NULL;
	all->texture[4].rel_path = NULL;
	all->nal.cel = 0;
	all->nal.fl = 0;
	all->nal.res = 0;
	all->nal.map = 0;
}

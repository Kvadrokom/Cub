/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:50:08 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/11 16:10:50 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parce_res(t_all *all, char *line)
{
	int i;

	i = 0;
	if (ft_strlen(line) > 1 && line[i + 1] == ' ')
	{
		i++;
		i = ft_res_move_space(line, i);
		if ((all->map_width = ft_atoi(&line[i])) == 0)
			print_error_free("Wrong format resolution");
		check_max_size(all, line, i, 'w');
		i = ft_res_move_dig(line, i);
		i++;
		if ((all->map_height = ft_atoi(&line[i])) == 0)
			print_error_free("Wrong format resolution");
		check_max_size(all, line, i, 'h');
		i = ft_res_move_space(line, i);
		i = ft_res_move_dig(line, i);
		i = ft_res_move_space(line, i);
		if (ft_isprint(line[i]) && !line[i])
			print_error_free("Wrong format resolution");
	}
	else
		print_error_free("Wrong format resolution");
	restr_res(all);
}

int		get_tex_path(char *line, t_all *all, int i)
{
	int			j;
	char		*str;

	j = (i == 4) ? 1 : 2;
	if (line[j] != ' ')
		return (0);
	while (line[j] == ' ')
		j++;
	if (!(str = ft_strtrim(&line[j], " ")))
		return (0);
	if (all->texture[i].rel_path)
		print_error_free("Duplicate line");
	all->texture[i].rel_path = str;
	return (1);
}

void	parce_tex_wl(t_all *all, char *line)
{
	if (!ft_strncmp("NO", line, 2))
	{
		if (!get_tex_path(line, all, 0))
			print_error_free("Wrong texture format");
	}
	else if (!ft_strncmp("EA", line, 2))
	{
		if (!get_tex_path(line, all, 1))
			print_error_free("Wrong texture format");
	}
	else if (!ft_strncmp("WE", line, 2))
	{
		if (!get_tex_path(line, all, 2))
			print_error_free("Wrong texture format");
	}
	else if (!ft_strncmp("SO", line, 2))
	{
		if (!get_tex_path(line, all, 3))
			print_error_free("Wrong texture format");
	}
	else
		print_error_free("Wrong texture format");
}

int		get_color(t_all *all, char *line, char c, int i)
{
	t_color color;

	if (!(ft_isdigit(line[i])))
		print_error_free("Wrong color format");
	color.r = ft_atoi(&line[i]);
	i += move_str(&line[i]);
	if (line[i] != ',')
		print_error_free("Wrong color format");
	i++;
	if (!(ft_isdigit(line[i])))
		print_error_free("Wrong color format");
	color.g = ft_atoi(&line[i]);
	i += move_str(&line[i]);
	if (line[i] != ',')
		print_error_free("Wrong color format");
	i++;
	if (!(ft_isdigit(line[i])))
		print_error_free("Wrong color format");
	color.b = ft_atoi(&line[i]);
	restr_color(&color);
	if (c == 'f')
		all->color_f = color;
	else
		all->color_c = color;
	return (i);
}

void	parce_fl_cl(t_all *all, char *line)
{
	int			i;

	i = 0;
	check_double_arg(line);
	check_numb_arg(&line[i], ' ', 2);
	if (line[i + 1] == ' ')
	{
		i++;
		while (line[i] == ' ')
			i++;
		check_numb_arg(&line[i], ',', 3);
		if (line[0] == 'F')
			i = get_color(all, line, 'f', i);
		else
			i = get_color(all, line, 'c', i);
		i += move_str(&line[i]);
		if (ft_isprint(line[i]) && line[i] != ' ')
			print_error_free("Wrong color format");
	}
	else
		print_error_free("Wrong color format");
}

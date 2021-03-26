/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:49:57 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/11 16:26:55 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(char *str, t_all *all)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	clear_all(all);
	exit(EXIT_FAILURE);
}

void	restr_res(t_all *all)
{
	static int count;

	count++;
	mlx_get_screen_size(all->mlx, &all->max_width, &all->max_height);
	if (count > 1)
		print_error_free("Duplicate lines");
	if (all->map_height > all->max_height)
		all->map_height = all->max_height;
	if (all->map_width > all->max_width)
		all->map_width = all->max_width;
	if (all->map_height < 0 || all->map_width < 0)
		print_error_free("Wrong format resolution");
	if (all->map_height < 240)
		all->map_height = 240;
	if (all->map_width < 320)
		all->map_width = 320;
}

int		make_val(int col)
{
	if (col > 255)
		col = 255;
	else if (col < 0)
		col = 0;
	return (col);
}

void	restr_color(t_color *color)
{
	color->r = make_val(color->r);
	color->g = make_val(color->g);
	color->b = make_val(color->b);
}

int		move_str(char *line)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

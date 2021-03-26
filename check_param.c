/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:33:47 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/06 11:49:11 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_free(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	exit(EXIT_FAILURE);
}

int		check_save(int arc, char **argv, t_all *all)
{
	if (arc > 3)
		print_error_free("Wrong number arguments");
	else if (arc == 3)
	{
		arc = 1;
		while (arc < 3)
		{
			if (!ft_strncmp("--save", argv[arc], 6))
			{
				all->save = 1;
				return (arc == 1 ? 2 : 1);
			}
			arc++;
		}
		print_error_free("Wrong input arguments");
	}
	all->save = 0;
	return (1);
}

void	check_nal(t_all *all)
{
	if (!all->nal.res || !all->nal.fl ||
		!all->nal.cel || !all->nal.map)
		print_error_free("Wrong file format");
}

void	check_double_arg(char *line)
{
	static int	f;
	static int	cl;

	if (*line == 'F')
		f++;
	else if (*line == 'C')
		cl++;
	if (f > 1 || cl > 1)
		print_error_free("Duplicate line");
}

int		check_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

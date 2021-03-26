/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 21:05:47 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/05 18:20:47 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_valid_file(char *str)
{
	int i;

	i = 0;
	while ((str[i]))
	{
		if (str[i] == '.')
		{
			if (ft_strlen(&str[i + 1]) != 3)
				print_error_free("Wrong input file");
			else if (!ft_strncmp(&str[i + 1], "cub", 3))
				return ;
			else
				print_error_free("Wrong input file");
		}
		i++;
	}
	print_error_free("Wrong input file");
}

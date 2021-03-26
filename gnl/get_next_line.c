/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:41:13 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/27 15:30:57 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_getchar(int fd)
{
	static int		ret;
	static char		*bufl;
	static char		buf[BUFFER_SIZE + 1];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (EOF);
	if (ret == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (-2);
		bufl = buf;
	}
	if (ret == 0)
		return (EOF);
	else
	{
		ret--;
		return ((unsigned char)*bufl++);
	}
}

int			get_line(int fd, char **line, int i, int n)
{
	char			c;

	while ((c = ft_getchar(fd)) != EOF)
	{
		if (c == -2)
			return (-1);
		if (c == '\n')
		{
			(*line)[i] = '\0';
			return (1);
		}
		(*line)[i] = c;
		++i;
		if (i == n)
		{
			if (!(*line = ft_resize(*line)))
				return (-1);
			n = 2 * n;
		}
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	int		i;
	int		n;

	n = BUFFER_SIZE;
	i = 0;
	if (!line)
		return (-1);
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!(*line = ft_strnew(BUFFER_SIZE + 1)))
		return (-1);
	return (get_line(fd, line, i, n));
}

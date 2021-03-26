/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:41:25 by skharjo           #+#    #+#             */
/*   Updated: 2020/12/30 15:26:53 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# define BUFFER_SIZE 32

int			ft_getchar(int fd);

int			get_next_line(int fd, char **line);

size_t		ft_strlen(const char *str);

char		*ft_strnew(int size);

char		*ft_resize(char *str);

int			get_line(int fd, char **line, int i, int n);

#endif

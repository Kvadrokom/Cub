/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:18:02 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/11 16:04:53 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int	write_bmp_header(int fd, int fsize, t_all *all)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, fsize);
	set_int_in_char(&bmpfileheader[10], 54);
	set_int_in_char(&bmpfileheader[14], 40);
	tmp = all->map_width;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = all->map_height;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[26] = (unsigned char)(1);
	set_int_in_char(&bmpfileheader[28], 24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int	get_color(t_all *all, int x, int y)
{
	int	rgb;
	int	color;

	color = my_mlx_pixel_get(all->win->line_length, all->win->addr,
							x, y);
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int	write_bmp_data(int fd, t_all *all, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = all->map_height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < all->map_width)
		{
			color = get_color(all, j, i);
			if (write(fd, &color, 3) < 0)
				return (0);
			j++;
		}
		if (pad > 0 && write(fd, &zero, pad) < 0)
			return (0);
		i--;
	}
	return (1);
}

int			save_bmp(t_all *all)
{
	int			fsize;
	int			fd;
	int			pad;

	pad = (4 - (all->map_width * 3) % 4) % 4;
	fsize = 54 + (3 * (all->map_width + pad) * all->map_height);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT
									| O_APPEND, 0666)) < 0)
		return (0);
	if (!write_bmp_header(fd, fsize, all))
		return (0);
	if (!write_bmp_data(fd, all, pad))
		return (0);
	close(fd);
	return (1);
}

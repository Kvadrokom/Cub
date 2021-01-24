#include "cub3d.h"

void	draw_col1(float x, float h, t_all *all, int color)
{
	float	y;

	if (h >= HEIGHT)
		h = HEIGHT - 1;
	if (h < 0)
		h = 0;
	y = HEIGHT / 2 + h / 2;
	while (h > 0)
	{
		my_mlx_pixel_put(all->win, x, y, color);
		h -= 1;
		y -= 1;
	}
}

void ft_cast_ray(t_all *all)
{
	t_plr ray;
	float start;
	float end;

	ray = *all->plr;
	all->plr->alfa = atan(all->plr->x / all->plr->y);
	start = all->plr->alfa - PI / 6;
	end = all->plr->alfa + PI / 6;
	while (start < end)
	{
		ray = *all->plr;
		while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_mlx_pixel_put(all->win, ray.x, ray.y, 0x990099);
		}
		start += PI / 720;
	}
}

void scale_img(t_data *img, int x, int y)
{
	int i;
	int j;
	float cx;
	float cy;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			cx = x + j;
			cy = y + i;
			my_mlx_pixel_put(img, cx, cy, 0xffffff);
			j++;
		}
		i++;
	}
}

void draw_2d_display(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->height)
	{
		j = 0;
		while (j < ft_strlen(all->map[i]))
		{
			if ((all->map)[i][j] == '1')
				scale_img(all->win->img, j * SCALE, i * SCALE);
			j++;
		}
		i++;
	}
	ft_cast_ray(all);
}
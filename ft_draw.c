#include "cub3d.h"

void	draw_col1(float x, float h, t_all *all, int color)
{
	float	y;
	int		i;

	if (h >= HEIGHT)
		h = HEIGHT - 1;
	if (h < 0)
		h = 0;
	y = HEIGHT / 2 - h / 2;
	i = 0;
	while (i < (int)h)
	{
		color = ft_texcolor(all, h, x, i);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(all->win, x, y, color);
		y += 1;
		i++;
	}
}

void	initexture(t_all *all)
{
	char	*relative_path[5];
	char	*tex_sprite;
	t_data 	tex[5];
	int		i;

	i = 0;
	relative_path[0] = "./redbricks.xpm";
	relative_path[1] = "./mossy.xpm";
	relative_path[2] = "./wood.xpm";
	relative_path[3] = "./greystone.xpm";
	relative_path[4] = "./barrel.xpm";
	while (i < 5)
	{
		all->texture[i] = tex[i];
		all->texture[i].img = mlx_xpm_file_to_image(all->vars->mlx, relative_path[i],
							&all->texture[i].img_width, &all->texture[i].img_height);
		all->texture[i].addr = mlx_get_data_addr(all->texture[i].img, &all->texture[i].bpp,
							&all->texture[i].line_length, &all->texture[i].endian);
		i++;
	}
}

void	ft_draw_tex(t_all *all, float x, float h)
{
	float	wall_x;
	// int		tex_x;
	float	step;
	char	*relative_path = "./redbricks.xpm";
	// int		img_width;
	// int 	img_height;
	t_data	tex;
	float	tex_pos;
	int		draw_start;
	int		draw_end;
	int		t;
	int		color;

	// tex.img = mlx_xpm_file_to_image(all->vars->mlx, relative_path, &img_width, &img_height);
	// tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length, &tex.endian);
	t = init_t(all);
	if (all->side == 0)
		wall_x = all->plr->y + all->raydir_y * all->pwalldist;
	else
		wall_x = all->plr->x + all->raydir_x * all->pwalldist;
	wall_x -= (int)wall_x;
	all->texture[t].tex_x = (int)(wall_x * (float)(all->texture[t].img_width));
	if ((all->side == 0 && all->raydir_x > 0) || (all->side == 1 && all->raydir_y < 0))
		all->texture[t].tex_x = all->texture[t].img_width - all->texture[t].tex_x - 1;
	step = 1 * all->texture[t].img_height / h;
	draw_start = -h / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = h / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start < draw_end)
	{
		tex_pos = (draw_start + h / 2 - HEIGHT / 2) * step;
		all->texture[t].tex_y = (int)tex_pos & (all->texture[t].img_height - 1);
		tex_pos += step;
		// ft_assert(tex_x < img_width && tex_y < img_height, "ERROR! Out of texture size");
		// ft_assert(tex_x >= 0 && tex_y >= 0, "ERROR! Out of texture size");
		color = my_mlx_pixel_get(all->texture[t].line_length, all->texture[t].addr, all->texture[t].tex_x, all->texture[t].tex_y,
		all->texture[0].bpp);
		my_mlx_pixel_put(all->win, x, draw_start, color);
		draw_start++;
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

int		init_t(t_all *all)
{
	int t;

	if (all->side == 0)
	{
		if (all->raydir_x > 0)
			t = 1;
		else if (all->raydir_x < 0)
			t = 2;
	}
	else if (all->side == 1)
	{
		if (all->raydir_y > 0)
			t = 3;
		else if (all->raydir_y < 0)
			t = 0;
	}
	return (t);
}


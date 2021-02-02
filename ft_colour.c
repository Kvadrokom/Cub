#include "cub3d.h"

unsigned int create_trgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void			gradient(t_data *img, int r,
						int g, int b)
{
	const size_t win_w = WIDTH;
	const size_t win_h = HEIGHT;
    int i = 0;
    int j;
    unsigned int c;

    while (i < win_h)
    {
        j = 0;
        while (j < win_w)
        {
            r = 255 * j / (float)win_w;
            g = 255 * i / (float)win_w;
            b = 0;
            c = create_trgb(r, g, b);
            my_mlx_pixel_put(img, j, i, c);
            j++;
        }
        i++;
    }
}

void	ft_assert(int cond, char *str)
{
	if (cond == 0)
	{
		ft_putendl_fd(str, 1);
		exit(1);
	}
}

int     ft_texcolor(t_all *all, float h, float x, int i)
{
    float   wall_x;
    int     tex_x;
    int     tex_y;
    int     color;
    int     t;

    t = init_t(all);
    if (all->side == 0)
    {
        wall_x = all->plr->y + all->raydir_y * all->pwalldist;
        tex_x = abs((int)((wall_x - (int)wall_x) * all->texture[t].img_width));
    }
    else
    {
        wall_x = all->plr->x + all->raydir_x * all->pwalldist;
        tex_x = abs((int)(((int)wall_x - wall_x) * all->texture[t].img_width));
    }

    if ((all->side == 0 && all->raydir_x > 0) || (all->side == 1 && all->raydir_y < 0))
        tex_x = all->texture[1].img_width - tex_x - 1;
    tex_y = (int)(i * (all->texture[t].img_height - 1) / (h - 1));
    // ft_assert(tex_x < all->texture[t].img_width && tex_y < all->texture[t].img_height, "ERROR! Out of texture size");
    // ft_assert(tex_x >= 0 && tex_y >= 0, "ERROR! Out of texture size");
    color = my_mlx_pixel_get(all->texture[t].line_length, all->texture[t].addr,
            tex_x, tex_y, all->texture[t].bpp);
    return (color);
}
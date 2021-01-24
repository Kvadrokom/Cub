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
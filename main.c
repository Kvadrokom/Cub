#include <stdio.h>
#include "cub3d.h"

int main() {
    t_vars 			vars;
    char			*line;
    t_plr			plr;
    t_all			all;
    t_data			img;

    all.height = ft_getmapheight();
    if (!(all.map = make_map(&line, all.height)))
        return (0);
    print_map(all.map);
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Cub3d");
    all.vars = &vars;
    all.plr = &plr;
    all.win = &img;
    initplr(&all);
    ft_draw_screen(&all);
    draw_2d_display(&all);
    mlx_hook(vars.win, 2, (1L << 0), key_hook, &all);
    mlx_loop(vars.mlx);
    return 0;
}

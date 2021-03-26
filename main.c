/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 21:07:04 by skharjo           #+#    #+#             */
/*   Updated: 2021/03/11 14:59:24 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_map(t_all *all)
{
	size_t	i;

	i = 0;
	while (i < all->height)
	{
		if (all->map[i])
			free(all->map[i]);
		i++;
	}
	if (all->map)
		free(all->map);
}

void	clear_sprites(t_all *all)
{
	int i;

	i = 0;
	if (all->sprite)
		free(all->sprite);
}

void	clear_tex(t_all *all)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (all->texture[i].rel_path)
		{
			free(all->texture[i].rel_path);
			all->texture[i].rel_path = NULL;
		}
		i++;
	}
}

void	clear_all(t_all *all)
{
	clear_tex(all);
	clear_sprites(all);
	clear_map(all);
}

int		main(int arc, char **argv)
{
	t_plr		plr;
	t_all		all;
	t_data		img;
	int			save_opt;

	if (arc > 1)
	{
		save_opt = check_save(arc, argv, &all);
		check_valid_file(argv[save_opt]);
		init_all(&all);
		config_file(&all, argv[save_opt]);
		check_nal(&all);
		set_mlx_param(&all);
		all.plr = &plr;
		all.win = &img;
		initplr(&all);
		init_sprites(&all);
		ft_initexture(&all);
		ft_draw_screen(&all);
		mlx_hook(all.mlx_win, 2, (1L << 0), key_hook, &all);
		mlx_hook(all.mlx_win, 17, (1L << 17), close_hook, &all);
		mlx_loop(all.mlx);
	}
	print_error_free("Wrong input");
	return (0);
}

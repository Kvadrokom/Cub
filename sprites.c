/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:18:40 by skharjo           #+#    #+#             */
/*   Updated: 2021/02/02 19:40:37 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int    get_numspr(t_all *all)
{
    unsigned int    num;
    int             i;
    int             j;

    i = 0;
    j = 0;
    num = 0;
    while (all->map[i])
    {
        j = 0;
        while (all->map[i][j])
        {
            if (all->map[i][j] == '2')
                num++;
            j++;
        }
        i++;
    }
        return (num);
}

void    ft_initsprs(t_all *all, t_sprite *sprite)
{
    int         i;
    int         j;
    int         z;
    
    i = 0;
    z = 0;
    while (all->map[i])
    {
        j = 0;
        while (all->map[i][j])
        {
            if (all->map[i][j] == '2')
            {
                sprite[z].x = j + .5;
                sprite[z].y = i + .5;
                z++;
            }
            j++;
        }
        i++;
    }
}

void    ft_distspr(t_all *all, unsigned int num, t_sprite *sprite)
{
    unsigned int i;

    i = 0;
    while (i < num)
    {
        sprite[i].dist = (all->plr->x - sprite[i].x) * (all->plr->x - sprite[i].x) +
                    (all->plr->y - sprite[i].y) * (all->plr->y - sprite[i].y);
        i++;
    }
}

void    ft_sort(t_sprite *sprite, unsigned int num)
{
    unsigned int    i;
    unsigned int    j;
    int             noswap;
    t_sprite        tmp;

    i = num - 1;
    while (i >= 0)
    {
        j = 0;
        noswap = 0;
        while (j < i)
        {
            if (sprite[j].dist < sprite [j + 1].dist)
            {
                tmp = sprite[j];
                sprite[j] = sprite[j + 1];
                sprite[j + 1] = sprite[j];
                noswap = 1;
            }
            j++;
        }
        if (noswap == 0)
            break;
        i++;
    }
}

void    ft_drawing(t_all *all, t_sprvals *data, t_sprite *sprite)
{
    int             drawstart_x;
    int             drawstart_y;
    int             drawend_x;
    int             drawend_y;
    int             stripe;
    int             d;
    int             color;

    drawstart_y = -data->spr_h / 2 + HEIGHT / 2;
    drawstart_y = (drawstart_y < 0) ? 0 : drawstart_y;
    drawend_y = data->spr_h / 2 + HEIGHT / 2;
    drawend_y = drawend_y >= HEIGHT ? HEIGHT - 1 : drawend_y;
    drawstart_x = data->sprscreen_x / 2 - data->spr_w / 2;
    drawstart_x = drawstart_x < 0 ? 0 : drawstart_x;
    drawend_x = data->sprscreen_x / 2 + data->spr_w / 2;
    drawend_x = drawend_x >= WIDTH ? WIDTH - 1 : drawend_x;
    stripe = drawstart_x;
    while (stripe < drawend_x)
    {
        all->texture[4].tex_x = (int)(256 * (stripe - (-data->spr_w / 2 + data->sprscreen_x))
                                * all->texture[4].img_width / data->spr_w) / 256;
        if (data->trans_y > 0 && stripe > 0 && stripe < WIDTH && data->trans_y < all->z_buff[stripe])
        {
            while (drawstart_y < drawend_y)
            {
                d = drawstart_y * 256 - HEIGHT * 128 + data->spr_h * 128;
                all->texture[4].tex_y = ((d * all->texture[4].img_height) / data->spr_h) / 256;
                color = my_mlx_pixel_get(all->texture[4].line_length, all->texture[4].addr,
                        all->texture[4].tex_x, all->texture[4].tex_y, all->texture[4].bpp);
                if((color & 0x00FFFFFF) != 0)
                    my_mlx_pixel_put(all->win, (float)stripe, (float)drawstart_y, color);
                drawstart_y++;
            }
        }
        stripe++;
    }
}

void    ft_draw_sprites(t_all *all)
{
    unsigned int    numspr;
    unsigned int    i;
    // int             drawstart_x;
    // int             drawstart_y;
    // int             drawend_x;
    // int             drawend_x;
    t_sprvals       data;
    t_sprite        *sprite;
    //int             *spr_order;
    float           *spr_dist;

    numspr = get_numspr(all);
    i = 0;
    if (numspr == 0)
        return ;
    ft_assert((sprite = malloc(sizeof(t_sprite) * numspr)) != NULL,
              "ERROR! Bad malloc allocation");
    // ft_assert((spr_dist = malloc(sizeof(int) * numspr)),
    //           "ERROR! Bad malloc allocation");
    ft_initsprs(all, sprite);
    ft_distspr(all, numspr, sprite);
    ft_sort(sprite, numspr);
    while (i < numspr)
    {
        data.sprite_x = sprite[i].x - all->plr->x;
        data.sprite_y = sprite[i].y - all->plr->y;
        data.inv_det = 1.0 / (all->plr->plane_x * all->plr->dir_y -
                        all->plr->dir_x * all->plr->plane_y);
        data.trans_x = data.inv_det * (all->plr->dir_y * data.sprite_x -
                        all->plr->dir_x * data.sprite_y);
        data.trans_y = data.inv_det * (-all->plr->plane_y * data.sprite_x
                        + all->plr->plane_x * data.sprite_y);
        data.sprscreen_x = (int)(WIDTH / 2 * (1 + data.trans_x / data.trans_y));
        data.spr_h = abs((int)(HEIGHT / data.trans_y));
        data.spr_w = abs((int)(WIDTH / data.trans_x));
        ft_drawing(all, &data, sprite);
        i++;
    }
}
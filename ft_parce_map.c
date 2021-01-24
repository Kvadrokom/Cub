#include "cub3d.h"

char *ft_makemap(char **line)
{
    char *map;
    int fd;

    fd = open("map.cub", O_RDONLY);
    map = ft_strnew(1);
    while (get_next_line(fd, line))
    {
        if (ft_atoi(*line))
            map = ft_strjoin(map, *line);
        free(*line);
    }
    return (map);
}

char **make_map(char **line, int size)
{
    char **map;
    int i;
    int fd;

    if ((fd = open("map.cub", O_RDONLY)) < 0)
        return (NULL);
    map = (char **)malloc(sizeof(char *) * (size + 1));
    i = 0;
    while (get_next_line(fd, line))
    {
        if (ft_atoi(*line))
            map[i++] = *line;
    }
    map[i++] = *line;
    map[i] = 0;
    close(fd);
    return (map);
}

void print_map(char **map)
{
    int i;

    i = 0;
    if (map == 0)
        return;
    while (map[i])
        ft_putendl_fd(map[i++], 1);
}

int ft_getmapheight()
{
    int i;
    int fd;
    char *line;

    if ((fd = open("map.cub", O_RDONLY)) < 0)
        exit(1);
    i = 0;
    while (get_next_line(fd, &line) > 0)
    {
        if (line)
        {
            if (ft_atoi(line))
                i++;
            free(line);
        }
    }
    i++;
    close(fd);
    return (i);
}

void initplr(t_all *all)
{
    int i;
    int j;
    char fv;

    i = 0;
    while (all->map[i])
    {
        j = 0;
        while (all->map[i][j])
        {
            if (ft_strchr("NSWE", all->map[i][j]))
            {
                all->plr->x = j + .5;
                all->plr->y = i + .5;
                fv = *(ft_strchr("NSWE", all->map[i][j]));
                if (fv == 'N')
                {
                    all->plr->dir_x = 0;
                    all->plr->dir_y = -1;
                }
                else if (fv == 'W')
                {
                    all->plr->dir_x = -1;
                    all->plr->dir_y = 0;
                }
                else if (fv == 'S')
                {
                    all->plr->dir_x = 0;
                    all->plr->dir_y = 1;
                }
                else
                {
                    all->plr->dir_x = 1;
                    all->plr->dir_y = 0;
                }
            }
            j++;
        }
        i++;
    }
}
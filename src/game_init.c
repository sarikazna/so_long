/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:59:10 by srudman           #+#    #+#             */
/*   Updated: 2024/03/19 20:34:16 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	put_image(t_map_data *map, void *img, int x, int y)
{
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, img, x, y);
}

void	img_render(t_map_data *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			if (map->matrix[y][x] == '0')
				put_image(map, map->img[0], x * 64, y * 64);
			if (map->matrix[y][x] == '1')
				put_image(map, map->img[1], x * 64, y * 64);
			if (map->matrix[y][x] == 'P')
				put_image(map, map->img[2], x * 64, y * 64);
			if (map->matrix[y][x] == 'C')
				put_image(map, map->img[3], x * 64, y * 64);
			if (map->matrix[y][x] == 'E')
				put_image(map, map->img[4], x * 64, y * 64);
			x++;
		}
		y++;
	}
}

void	check_if_image_failed(t_map_data *map, void *img)
{
	if (img == NULL)
	{
		write(1, "Error\nThere is an issue with an .xpm file.\n", 43);
		exit_game(&map);
	}
}

static void	img_init(t_map_data *m)
{
	int	s;

	s = 64;
	m->img = malloc(7 * sizeof(void *));
	if (m->img == NULL)
		return ;
	m->img[0] = mlx_xpm_file_to_image(m->mlx_ptr, "img/path.xpm", &s, &s);
	check_if_image_failed(m, m->img[0]);
	m->img[1] = mlx_xpm_file_to_image(m->mlx_ptr, "img/wall.xpm", &s, &s);
	check_if_image_failed(m, m->img[1]);
	m->img[2] = mlx_xpm_file_to_image(m->mlx_ptr, "img/player.xpm", &s, &s);
	check_if_image_failed(m, m->img[2]);
	m->img[3] = mlx_xpm_file_to_image(m->mlx_ptr, "img/collect.xpm", &s, &s);
	check_if_image_failed(m, m->img[3]);
	m->img[4] = mlx_xpm_file_to_image(m->mlx_ptr, "img/exit.xpm", &s, &s);
	check_if_image_failed(m, m->img[4]);
	m->img[5] = mlx_xpm_file_to_image(m->mlx_ptr, "img/p_over_e.xpm", &s, &s);
	check_if_image_failed(m, m->img[5]);
	m->img[6] = NULL;
}

int	game_init(t_map_data *map)
{
	map->mlx_ptr = mlx_init();
	if (!map->mlx_ptr)
	{
		mlx_destroy_display(map->mlx_ptr);
		return (0);
	}
	map->win_ptr = mlx_new_window(map->mlx_ptr, (map->columns * 64), 
			(map->rows * 64), "so_long");
	if (!map->win_ptr)
	{
		mlx_destroy_window(map->mlx_ptr, map->win_ptr);
		mlx_destroy_display(map->mlx_ptr);
		return (0);
	}
	img_init(map);
	img_render(map);
	return (1);
}

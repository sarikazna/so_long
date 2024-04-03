/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:53:58 by srudman           #+#    #+#             */
/*   Updated: 2024/03/20 14:00:33 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	is_error(t_map_data *map, char *matrix_tmp)
{
	write(1, "Error\nMap should start/end with '1'.\n", 37);
	free(matrix_tmp);
	exit_game(&map);
}

void	checks_and_split(t_map_data *map, char *matrix_tmp)
{
	int	i;

	i = 0;
	if (!matrix_tmp[0])
		is_error(map, matrix_tmp);
	while (matrix_tmp[i + 1])
	{
		if (matrix_tmp[i] == '\n' && matrix_tmp[i + 1] == '\n')
			is_error(map, matrix_tmp);
		i++;
	}
	if (matrix_tmp[i] != '1' || matrix_tmp[0] != '1')
		is_error(map, matrix_tmp);
	map->matrix = ft_split(matrix_tmp, '\n');
	free(matrix_tmp);
}

/* We open the map and put the map data into variable map->matrix. */

void	ft_retrieve_matrix(t_map_data *map, char *path)
{
	char	*matrix_tmp;
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\nCould not open the file.\n", 31);
		exit_game(&map);
	}
	matrix_tmp = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		matrix_tmp = ft_strjoin_modified(matrix_tmp, line);
		free(line);
	}
	checks_and_split(map, matrix_tmp);
	close(fd);
}

/* 
Functions arguments_are_valid checks
- if we get exactly 2 arguments from the terminal and
- if the 2nd argument (the path to the game map) is correct. Specifically if
the name of the file ends with .ber
*/

int	arguments_are_valid(int argc, char *map_path)
{
	int	i;

	if (argc != 2 || !map_path)
	{
		write(1, "Error\nExactly two arguments needed.\n", 36);
		return (0);
	}
	i = 0;
	while (map_path[i++])
		;
	if (map_path[i - 1] == '\0' && map_path[i - 2] == 'r' && 
		map_path[i - 3] == 'e' && map_path[i - 4] == 'b' 
		&& map_path[i - 5] == '.')
		return (1);
	else
	{
		write(1, "Error\nFile name invalid.\n", 25);
		return (0);
	}
}

int	main(int argc, char **argv)
{
	t_map_data	*map;

	map = NULL;
	if (arguments_are_valid(argc, argv[1]))
	{
		if (!ft_map_init(&map))
			return (-1);
		ft_retrieve_matrix(map, argv[1]);
		if (map->matrix == NULL || !ft_validate_map(map, argv[1]))
		{
			free_map_struct(map);
			return (-1);
		}
		game_init(map);
		play_game(map);
		if (map->win_ptr)
			mlx_destroy_window(map->mlx_ptr, map->win_ptr);
		if (!map->mlx_ptr)
			mlx_destroy_display(map->mlx_ptr);
	}
	free_map_struct(map);
	free(map);
	return (0);
}

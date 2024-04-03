/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:10:43 by srudman           #+#    #+#             */
/*   Updated: 2024/03/20 13:55:15 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*
Function ft_map_is_rectangular checks that each of the line in the map is the
same size. This includes empty lines that may appear on the map.
*/

int	ft_map_is_rectangular(t_map_data *map)
{
	int	i;

	map->columns = ft_strlen(map->matrix[0]);
	i = 0;
	while (map->matrix[i])
	{
		if (ft_strlen(map->matrix[i]) <= 2)
		{
			write(1, "Error\nEach line should be the same length.\n", 43);
			return (0);
		}
		if (ft_strlen(map->matrix[i]) != ft_strlen(map->matrix[0]))
		{
			write(1, "Error\nEach line should be the same length.\n", 43);
			return (0);
		}
		i++;
		map->rows++;
	}
	return (1);
}

/*
Fucntion ft_validate_walls validates whether or not the game matrix is 
surrounded by walls (as required by the project instruction). Walls are 
marked with the number '1'.
*/

int	ft_validate_walls(t_map_data *map)
{
	int	i;

	i = 0;
	while (i < map->columns)
	{
		if (map->matrix[0][i] != '1' || map->matrix[map->rows - 1][i] != '1')
		{
			ft_putstr_fd("Error\nWalls are missing on the edges.\n", 1);
			return (0);
		}
		i++;
	}
	i = 0;
	while (map->matrix[i])
	{
		if (map->matrix[i][0] != '1' || map->matrix[i][map->columns - 1] != '1')
		{
			ft_putstr_fd("Error\nWalls are missing on the edges.\n", 1);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
Function ft_validate_count is a continuation ft_count_elements. It checks
that all the item counts are in line with the project requirements and reports
error in case they are not.
*/

int	ft_validate_count(t_map_data *map)
{
	if (map->score == 0)
	{
		ft_putstr_fd("Error\nThe game map should contain collectables.\n", 1);
		return (0);
	}
	if (map->no_exits != 1)
	{
		ft_putstr_fd("Error\nThe game map should contain exactly one exit.\n", 1);
		return (0);
	}
	if (map->no_players_check != 1)
	{
		ft_putstr_fd("Error\nThe game map should contain exactly 1 player.\n", 1);
		return (0);
	}
	return (1);
}

/*
Function ft_count_elements counts the number of elements in the game map.
It counts the number of columns (rows were counter in another function),
the number of C (collectables), E (exits), P (players) and saves the data
in the struct called 'map'.
*/

int	ft_count_elements(t_map_data *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->matrix[j])
	{
		i = 0;
		while (i < map->columns)
		{
			if (map->matrix[j][i] == 'C')
				map->score++;
			if (map->matrix[j][i] == 'E')
				map->no_exits++;
			if (map->matrix[j][i] == 'P')
				map->no_players_check++;
			if (map->matrix[j][i] == 'X')
				map->no_enemies++;
			i++;
		}
		j++;
	}
	return (ft_validate_count(map));
}

/*
ft_validate_map checks if the map is rectangular, is the game contains walls
all around, if there are collectables, exits and a player, and if it does
not contain an invalide character.

Then we have to validate the path. We do this with flood filling algortim
ft_flood_fill. But furst we need to lay down some fundamentals to then call 
the flood filling algorithm. For instance with ft_assign_position we assign 
the position of player 'P'. This is important because we have to denote the 
starting position. In the flood filling algorith we also borrow a variables 
like map->curr_score that have other uses in our program so  we reset it 
after the algorithm is finished. map->no_exits contains a value prior to 
ft_validate_path but we no longer need that value so we reset it to
0 and count the number of exits again. The previous value contained all the 
exists. The new value of map->no_exits contains the number of all accessible
exits.

Then we open the file again to rewrite matrix since the flood filling 
algorithm changed many values in the matrix.
*/

int	ft_validate_map(t_map_data *map, char *path_to_file)
{
	int	fd;

	if (!ft_map_is_rectangular(map) || !ft_validate_walls(map) 
		|| !ft_count_elements(map) || !ft_allowed_character(map))
		exit_game(&map);
	ft_assign_position(map);
	map->no_exits = 0;
	ft_flood_fill(map->player_x, map->player_y, map);
	if (!(map->no_exits >= 1 && map->curr_score == map->score))
	{
		ft_putstr_fd("Error\nPath is invalid.\n", 1);
		exit_game(&map);
	}
	map->curr_score = 0;
	fd = open(path_to_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCould not open the file.", 1);
		exit_game(&map);
	}
	ft_rewrite_matrix(map, fd);
	return (1);
}

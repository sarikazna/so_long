/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:50:12 by srudman           #+#    #+#             */
/*   Updated: 2024/03/19 17:30:51 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* 
ft_flood_fill rewrote fields P, C and O into '1' in the matrix so now 
we needed to rewrite matrix back to the original values. We do this in
function ft_rewrite_matrix.
*/

void	ft_rewrite_matrix(t_map_data *map, int fd)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	while (map->matrix[j])
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (i < map->columns)
		{
			if (line[i] != map->matrix[j][i])
				map->matrix[j][i] = line[i];
			i++;
		}
		free(line);
		j++;
	}
	close(fd);
}

/* 
I used flood filling algorithm to validate that the path from 'P' player 
to 'E' exit is a valid one. The player must also be able to gather all 
collectibles 'C'. 
The traditional flood-fill  algorithm takes three parameters: a start node, 
a target color, and a replacement color. The algorithm looks for all nodes in
the array that are  connected to the start node by a path of the target color 
and changes them to the replacement color.
In my case I changed visited fields P, C and O into '1' which denotes a wall 
rather than a new colour.
*/

void	ft_flood_fill(int x, int y, t_map_data *map)
{
	if (map->matrix[y][x] == '1') 
		return ;
	if (map->no_exits >= 1 && map->curr_score == map->score)
		return ;
	if (map->matrix[y][x] == 'E')
		map->no_exits++;
	if (map->matrix[y][x] == 'C')
		map->curr_score++;
	map->matrix[y][x] = '1';
	if (map->matrix[y + 1][x] != '1')
		ft_flood_fill(x, y + 1, map);
	if (map->matrix[y - 1][x] != '1')
		ft_flood_fill(x, y - 1, map);
	if (map->matrix[y][x + 1] != '1')
		ft_flood_fill(x + 1, y, map);
	if (map->matrix[y][x - 1] != '1')
		ft_flood_fill(x - 1, y, map);
	return ;
}

/* 
In ft_assign_position we assign the X and Y position of 'P' player.
*/

void	ft_assign_position(t_map_data *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->matrix[j])
	{
		i = 0;
		while (i < map->columns)
		{
			if (map->matrix[j][i] == 'P')
			{
				map->player_y = j;
				map->player_x = i;
			}
			i++;
		}
		j++;
	}
}

/*
ft_validate_part is intended to lay down some fundamentals to then call the 
flood filling algorithm. For instance with ft_assign_position we assign the 
position of player 'P'. This is important because we have to denote the starting
positio we
borrow a variables like map->curr_score that have other uses in our program so 
we reset it after the algorithm is finished. map->no_exits contains a value
prior to ft_validate_path but we no longer need that value so we reset it to
0 and count the number of exits again. The previous value contained all the 
exists. The new value of map->no_exits contains the number of all accessible
exits.
*/

/*
We need to make sure no invalid characters are present int our maps. 
The only allowed characters are 01CEP and \n.
*/
int	ft_allowed_character(t_map_data *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->matrix[j])
	{
		i = 0;
		while (i < map->columns)
		{
			if (map->matrix[j][i] != 'C' && map->matrix[j][i] != 'E' 
				&& map->matrix[j][i] != 'P' && map->matrix[j][i] != '1' 
				&& map->matrix[j][i] != '0' && map->matrix[j][i] != '\n')
			{
				write(1, "Error\nMap contains invalid characters.\n", 39);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

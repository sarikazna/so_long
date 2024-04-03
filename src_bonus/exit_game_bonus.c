/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:04:33 by srudman           #+#    #+#             */
/*   Updated: 2024/03/16 18:18:39 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	exit_game(t_map_data **map)
{
	(*map)->game_running = 0;
	free_map_struct(*map);
	if ((*map)->mlx_ptr != NULL)
	{
		mlx_destroy_window((*map)->mlx_ptr, (*map)->win_ptr);
		mlx_destroy_display((*map)->mlx_ptr);
		free((*map)->mlx_ptr);
	}
	free(*map);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:00:25 by srudman           #+#    #+#             */
/*   Updated: 2024/03/28 23:49:33 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/* This function makes sure the player does not move into a wall. It also
cannot move into an exit if the player hasn't collected all collectables.
The subject requires us to display number of moves/steps of the player in
the Shell. So if we validate that the move is valid we will count +1
towards the total number of steps/moves and write this information into
the shell using the write function. */

int	move_is_valid(t_map_data *map, int x, int y)
{
	if (map->matrix[y][x] == '0' || map->matrix[y][x] == 'C' 
		|| map->matrix[y][x] == 'E')
	{
		map->steps++;
		ft_putstr_fd("Number of moves: ", 1);
		ft_putnbr_fd(map->steps, 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	else
		return (0);
}

/* This function is called by 
mlx_hook(map->win_ptr, 17, 1L<<19, &on_destroy, &map)
It ends the game once the X on the window is being pressed. */

int	on_destroy(t_map_data **map)
{
	if (!(*map)->game_running)
		return (0);
	(*map)->game_running = 0;
	write(1, "You have exited the game.\n", 27);
	exit_game(map);
	return (0);
}

/* This function is called by mlx_key_hook(map->win_ptr, handle_input, &map)
It ends the game once you press ESC on the keyboard. */

int	handle_input(int keysym, t_map_data **map)
{
	if (!(*map)->game_running)
		return (0);
	if (keysym == KEY_ESC)
	{
		(*map)->game_running = 0;
		write(1, "You have exited the game.\n", 27);
		exit_game(map);
	}
	if ((keysym == KEY_W || keysym == KEY_UP) && move_is_valid
		(*map, (*map)->player_x, ((*map)->player_y - 1)))
		move_up(*map);
	if ((keysym == KEY_S || keysym == KEY_DOWN) && move_is_valid
		(*map, (*map)->player_x, ((*map)->player_y + 1)))
		move_down(*map);
	if ((keysym == KEY_A  || keysym == KEY_LEFT) && move_is_valid
		(*map, ((*map)->player_x - 1), (*map)->player_y))
		move_left(*map);
	if ((keysym == KEY_D  || keysym == KEY_RIGHT) && move_is_valid
		(*map, ((*map)->player_x + 1), (*map)->player_y))
		move_right(*map);
	return (0);
}

/* Function play_game handles key board inputs of W S A D (up, down, left, 
right) and Ecs by calling mlx_key_hook. mlx_hook handles a mouse press on 
the X sign in the window. mlx_loop keeps the game running.
*/

int	play_game(t_map_data *map)
{
	mlx_key_hook(map->win_ptr, handle_input, &map);
	mlx_hook(map->win_ptr, 17, 1L << 19, &on_destroy, &map);
	mlx_loop(map->mlx_ptr);
	exit(0);
	return (1);
}

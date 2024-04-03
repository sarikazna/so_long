/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:10:52 by srudman           #+#    #+#             */
/*   Updated: 2024/03/28 23:44:01 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../.mlx/mlx.h"
# include <string.h>

/* DATA TYPES */

/* Keycodes on a keyboard */
# define KEY_ESC			65307
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP  			65362
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363
# define KEY_DOWN  			65364

/* STRUCTS */

/* t_map_data is a struct containing info on the the game layout. 
> int 	player_posX and Y = position on the matrix with X and Y axis;
> int score = number of collec<string.h>table in the game;
> int curr_score = number of collected collectables, the game starts with 0; 
> void *wall, *exit, *items, *player, *enemy = points to the image of each;
*/
typedef struct s_map_data
{
	char	**matrix;
	int		rows;
	int		columns;
	int		height;
	int		width;
	int		no_exits;
	int		no_players_check;
	int		player_x;
	int		player_y;
	int		score;
	int		curr_score;
	void	**img;
	void	*mlx_ptr; 
	void	*win_ptr;
	int		no_enemies;
	int		steps;
	int		game_running;
}	t_map_data;

/*  FUNCTIONS */
void	free_map_struct(t_map_data *map);
int		ft_map_init(t_map_data **map);
int		ft_validate_map(t_map_data *map, char *path_to_file);
int		ft_allowed_character(t_map_data *map);
void	ft_assign_position(t_map_data *map);
void	ft_flood_fill(int x, int y, t_map_data *map);
void	ft_rewrite_matrix(t_map_data *map, int fd);
void	put_image(t_map_data *map, void *img, int x, int y);
int		game_init(t_map_data *map);
int		play_game(t_map_data *map);
void	move_up(t_map_data *map);
void	move_down(t_map_data *map);
void	move_left(t_map_data *map);
void	move_right(t_map_data *map);
void	exit_game(t_map_data **map);
// void	move_player(t_map_data *map, int new_x, int new_y);

#endif
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:51:52 by srudman           #+#    #+#              #
#    Updated: 2024/03/19 18:44:18 by srudman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
INCLUDES = -I/usr/include -Imlx -I./inc

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
LIBFT_DIR = ./libft
MLX_DIR = ./.mlx

SRCS = 		src/exit_game.c src/game_init.c src/main.c src/map_struct_utils.c \
			src/movements.c src/play_game.c src/validate_map.c \
			src/validate_map2.c
SRCS_BONUS = src_bonus/exit_game_bonus.c src_bonus/game_init_bonus.c \
			src_bonus/main_bonus.c src_bonus/map_struct_utils_bonus.c \
			src_bonus/movements_bonus.c src_bonus/play_game_bonus.c \
			src_bonus/validate_map_bonus.c src_bonus/validate_map2_bonus.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make --directory=$(LIBFT_DIR)
	@make --directory=$(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@make --directory=$(LIBFT_DIR)
	@make --directory=$(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME_BONUS)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

clean:
	@make clean --directory=$(LIBFT_DIR)
	@make clean --directory=$(MLX_DIR)
	$(RM) -r $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	@make fclean --directory=$(LIBFT_DIR)
	@make clean --directory=$(MLX_DIR)
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all bonus
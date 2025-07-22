/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:05 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/07/16 12:11:02 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_input(int key, t_data *game)
{

    if (key == 65307)
        exit(0);
    
    if (key == MOVE_UP || key == ARROW_UP)
        game->input.key_up = 1;
    if (key == MOVE_DOWN || key == ARROW_DOWN)
        game->input.key_down = 1;
    if (key == MOVE_LEFT || key == ARROW_LEFT)
        game->input.key_left = 1;
    if (key == MOVE_RIGHT || key == ARROW_RIGHT)
        game->input.key_right = 1;
    update_player_directions(game);
    return (0);
}

int handle_key_release(int key, t_data *game)
{
    if (key == MOVE_UP || key == ARROW_UP)
        game->input.key_up = 0;
    if (key == MOVE_DOWN || key == ARROW_DOWN)
        game->input.key_down = 0;
    if (key == MOVE_LEFT || key == ARROW_LEFT)
        game->input.key_left = 0;
    if (key == MOVE_RIGHT || key == ARROW_RIGHT)
        game->input.key_right = 0;
    update_player_directions(game);
    return (0);
}

void update_player_directions(t_data *game)
{
    game->player.walkDirection = 0;
    game->player.turnDirection = 0;
    
    if (game->input.key_up)
        game->player.walkDirection = 1;
    if (game->input.key_down)
        game->player.walkDirection = -1;
    if (game->input.key_left)
        game->player.turnDirection = -1;
    if (game->input.key_right)
        game->player.turnDirection = 1;
}

int	close_game(t_data *game)
{
	// free_textures(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->map)
		free_split(game->map);
	exit(0);
	return (0);
}
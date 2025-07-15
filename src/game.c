#include "cub3d.h"

int	handle_input(int key, t_data *game)
{
	if (key == 65307)
		close_game(game);
	if (key == MOVE_UP || key == ARROW_UP)
		update(key, game);
	if (key == MOVE_LEFT || key == ARROW_LEFT)
		update(key, game);
	if (key == MOVE_RIGHT || key == ARROW_RIGHT)
		update(key, game);
	if (key == MOVE_DOWN || key == ARROW_DOWN)
		update(key, game);
	render_map(game);
	return (0);
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
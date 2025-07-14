/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:41:51 by lsadi             #+#    #+#             */
/*   Updated: 2025/07/13 16:41:55 by lsadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	is_border(t_data *data, int x, int y)
// {
// 	if (y == 0 || y == data->map_height - 1)
// 		return (1);
// 	if (x == 0)
// 		return (1);
// 	if (x >= (int)ft_str_len(data->map[y]) - 1)
// 		return (1);
// 	return (0);
// }

static int get_max_width(t_data *data)
{
	int max_width;
	int current_width;
	int i;

	max_width = 0;
	i = 0;
	while (i < data->map_height)
	{
		current_width = ft_str_len(data->map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int is_border(t_data *data, int x, int y)
{
	int max_width;

	max_width = get_max_width(data);	
	if (y == 0 || y == data->map_height - 1)
		return (1);
	if (x == 0 || x == max_width - 1)
		return (1);	
	return (0);
}

void flood_fill(char **map, int x, int y, t_data *data, int *valid)
{
    char current_char;

    // Conditions d'arrêt
    if (*valid == 0)
        return;
    if (y < 0 || y >= data->map_height)
        return;
    if (x < 0 || x >= (int)ft_str_len(map[y]))
        return;
    
    // Utiliser la carte copiée, pas get_char_at !
    current_char = map[y][x];
    
    // Si on trouve un mur/visité
    if (current_char == '1' || current_char == 'V')
        return;
    
    // Si on trouve un espace, c'est OK (zone inaccessible)
    if (current_char == ' ')
        return;
    
    // Vérifier si on est sur une vraie bordure
    if (is_border(data, x, y))
    {
        *valid = 0;
        return;
    }
    
    // Marquer comme visité
    map[y][x] = 'V';

    // Récursion dans les 4 directions
    flood_fill(map, x - 1, y, data, valid);
    flood_fill(map, x + 1, y, data, valid);
    flood_fill(map, x, y - 1, data, valid);
    flood_fill(map, x, y + 1, data, valid);
}

// void	flood_fill(char **map, int x, int y, t_data *data, int *valid)
// {
// 	if (*valid == 0)
// 		return ;
// 	if (y < 0 || y >= data->map_height)
// 		return ;
// 	if (x < 0 || x >= (int)ft_str_len(map[y]))
// 		return ;
// 	if (is_border(data, x, y))
// 	{
// 		*valid = 0;
// 		return ;
// 	}
// 	if (map[y][x] == '1' || map[y][x] == 'V')
// 	{
// 		printf("Wall or visited at (%d, %d)\n", x, y);
// 		return ;
// 	}
// 	map[y][x] = 'V';
// 	flood_fill(map, x - 1, y, data, valid);
// 	flood_fill(map, x + 1, y, data, valid);
// 	flood_fill(map, x, y - 1, data, valid);
// 	flood_fill(map, x, y + 1, data, valid);
// }

char	**copy_map(t_data *data)
{
	char	**dup_map;
	int		i;

	dup_map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (i < data->map_height)
	{
		dup_map[i] = ft_strdup(data->map[i]);
		if (!dup_map[i])
		{
			while (--i >= 0)
				free(dup_map[i]);
			free(dup_map);
			return (NULL);
		}
		i++;
	}
	dup_map[data->map_height] = NULL;
	return (dup_map);
}

void	free_copy(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	check_path(t_data *data)
{
	char	**map_copy;
	int		valid;

	map_copy = copy_map(data);
	if (!map_copy)
		return (0);
	valid = 1;
	flood_fill(map_copy, data->player.x, data->player.y, data, &valid);
	free_copy(map_copy, data->map_height);
	return (valid);
}

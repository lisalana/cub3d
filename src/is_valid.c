#include "cub3d.h"

// VALIDATION DES BORDURES

int check_line(t_data *data, int line_index)
{
	int j;
	char *line;

	line = data->map[line_index];
	j = 0;
	while (line[j])
	{
		if (line[j] != '1' && line[j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int check_sides(t_data *data, int i)
{
	int j;
	int len;

	// Vérifier premier caractère non-espace
	j = 0;
	while (data->map[i][j] == ' ')
		j++;
	if (data->map[i][j] && data->map[i][j] != '1')
		return (0);

	// Vérifier dernier caractère non-espace  
	len = ft_str_len(data->map[i]);
	j = len - 1;
	while (j >= 0 && data->map[i][j] == ' ')
		j--;
	if (j >= 0 && data->map[i][j] != '1')
		return (0);
	return (1);
}

int check_walls(t_data *data)
{
	int i;

	// Vérifier première ligne
	if (!check_line(data, 0))
		return (0);
	// Vérifier dernière ligne
	if (!check_line(data, data->map_height - 1))
		return (0);
	// Vérifier côtés pour lignes intermédiaires
	i = 1;
	while (i < data->map_height - 1)
	{
		if (!check_sides(data, i))
			return (0);
		i++;
	}
	return (1);
}

// VALIDATION DES ESPACES

int check_pos(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (1);
	if (x < 0 || x >= (int)ft_str_len(data->map[y]))
		return (1);
	if (data->map[y][x] != '1' && data->map[y][x] != ' ')
		return (0);
	return (1);
}

int check_around(t_data *data, int x, int y)
{
	if (!check_pos(data, x - 1, y))
		return (0);
	if (!check_pos(data, x + 1, y))
		return (0);
	if (!check_pos(data, x, y - 1))
		return (0);
	if (!check_pos(data, x, y + 1))
		return (0);
	return (1);
}

int check_spaces(t_data *data)
{
	int y;
	int x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == ' ')
			{
				if (!check_around(data, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

// VALIDATION DES FICHIERS DE TEXTURE 

int file_exists(char *filename)
{
	int fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int check_files(t_config *config)
{
	if (!file_exists(config->texture_north))
		return (0);
	if (!file_exists(config->texture_south))
		return (0);
	if (!file_exists(config->texture_west))
		return (0);
	if (!file_exists(config->texture_est))
		return (0);
	return (1);
}

// VALIDATION PRINCIPALE

int check_map(t_data *data)
{
	// 1. Vérifier contenu de la carte AVANT de modifier quoi que ce soit
	if (!check_content(data))
	{
		printf("Error\nInvalid characters in map\n");
		return (0);
	}
	// 2. Vérifier qu'on a un joueur
	if (!find_player(data))
	{
		printf("Error\nNo player or multiple players found\n");
		return (0);
	}
	// 3. Vérifier que la carte est fermée
	if (!check_walls(data))
	{
		printf("Error\nMap is not closed by walls\n");
		return (0);
	}
	// 4. Vérifier espaces
	if (!check_spaces(data))
	{
		printf("Error\nInvalid space configuration\n");
		return (0);
	}
	// 5. Vérifier acces
	if (!check_path(data))
	{
		printf("Error\nPlayer area is not properly enclosed\n");
		return (0);
	}
	// 6. Vérifier fichiers de texture
	if (!check_files(&data->config))
	{
		printf("Error\nTexture files not found\n");
		return (0);
	}
	return (1);
}

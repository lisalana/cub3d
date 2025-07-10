#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "../get_next_line/get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct s_config
{
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_est;
	int			floor_color;
	int			ceiling_color;
}				t_config;

typedef struct s_player
{
	int			x;
	int			y;
	char		direction; // N, S, E, W
}				t_player;

typedef struct s_data
{
	t_config	config;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
}				t_data;

int	parse_file(const char *filename, t_data	*data);


#endif

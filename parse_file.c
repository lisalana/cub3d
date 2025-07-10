#include "cub3d.h"

int	parse_file(const char *filename, t_data	*data)
{
	int		fd;
	char	*line;
	(void)data;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		if (is_texture_line(line))
			parse_texture_line(line, &data->config);
		if (is_color_line(line))
			parse_color_line(line, &data->config);
		else
			printf("ligne inconnue\n");
		free(line);
	}
	// {
	// 	printf("ligne lue : %s", line);
	// 	free(line);
	// }
	close(fd);
	return(0);
}

int		is_texture_line(char *line)
{
	if (!line)
		return(0);
	if (strncmp(line, "NO ", 3) == 0)
		return (1);
	if (strncmp(line, "SO ", 3) == 0)
		return (1);
	if (strncmp(line, "WE ", 3) == 0)
		return (1);
	if (strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

int		parse_texture_line(char *line, t_config config)
{

}
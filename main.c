#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	if (ac != 2)
	{
		printf("usage: %s <map.cub>\n", av[0]);
		return (1);
	}
	if (parse_file(av[1], &data))
	{
		printf("Erreur pendant le parsing\n");
		return (1);
	}
	printf("Parsing termine\n");
	return (0);
}
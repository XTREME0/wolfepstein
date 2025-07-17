#include "../cub3d.h"

int	tab_len(char **tab)
{
	int	i;

	if (tab == NULL)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	tab_join(t_cube *cube, char *line)
{
	char	**new_map;
	int		i;

	if (line == NULL)
		return (-1);
	new_map = malloc(sizeof(char *) * (tab_len(cube->map) + 2));
	if (new_map == NULL)
		return (-1);
	if (cube->map == NULL)
	{
		cube->map = new_map;
		cube->map[0] = line;
		cube->map[1] = NULL;
		return (0);
	}
	i = 0;
	while (cube->map[i])
	{
		new_map[i] = cube->map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(cube->map);
	cube->map = new_map;
	return (0);
}

int	banned_char(char c)
{
	if (c != ' ' && c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

int	check_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (banned_char(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_map(t_cube *cube, int fd)
{
	int	max_x;
	int	max_y;
	char	*line;

	while (1)
	{
		line = rm_newline(get_next_line(fd));
		if (line == NULL)
			break ;
		if (check_map_line(line))
			return (free(line), 1);
		if (tab_join(cube, line))
			return (free(line), 1);
	}
	return (0);
}

#include "../cub3D.h"

void	fill_cub_null(t_cube *cube, char **new_map, char *line)
{
	cube->map = new_map;
	cube->map[0] = line;
	cube->map[1] = NULL;
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
		fill_cub_null(cube, new_map, line);
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
	if (c != ' ' && c != '1' && c != '0' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

int	is_valid_stop(char c)
{
	if (c == '0' || c == '1' || is_player(c))
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

#include "../cub3D.h"

int	first_last_line(t_cube *cube)
{
	int		i;
	char	*line;

	i = 0;
	line = cube->map[0];
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	mid_line(t_cube *cube, int y)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	line = cube->map[y];
	len = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '0' || is_player(line[i]))
		{
			if (check_surroundings(cube, line, i, y))
				return (1);
		}
		i++;
	}
	return (0);
}

int	map_check(t_cube *cube)
{
	int	i;
	int	len;

	if (cube->map == NULL)
		return (1);
	len = tab_len(cube->map);
	if (len < 3)
		return (1);
	i = 0;
	while (cube->map[i])
	{
		if (i == 0 || i == len - 1)
		{
			if (first_last_line(cube))
				return (1);
		}
		else
		{
			if (mid_line(cube, i))
				return (1);
		}
		i++;
	}
	return (0);
}

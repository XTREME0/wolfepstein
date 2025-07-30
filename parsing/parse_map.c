#include "../cub3D.h"

int	tab_len(char **tab)
{
	int	i;

	if (tab == NULL)
		return (0);
	i = 0;
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
	if (c != ' ' && c != '1' && c != '0' && c != 'N'
			&& c != 'S' && c != 'E' && c != 'W')
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

int	player_in_line(char *line, int *player)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_player(line[i]))
			*player = *player + 1;
		i++;
	}
	return (*player);
}

int	parse_map(t_cube *cube, int fd)
{
	char	*line;
	int		player;

	player = 0;
	while (1)
	{
		line = rm_newline(get_next_line(fd));
		if (line == NULL)
			break ;
		if (line[0] == '\0' || is_all_space(line))
		{
			free(line);
			continue ;
		}
		if (player_in_line(line, &player) > 1)
				return (free(line), 1);
		if (check_map_line(line))
			return (free(line), 1);
		if (tab_join(cube, line))
			return (free(line), 1);
	}
	if (player == 0)
		return (1);
	return (0);
}

int	is_valid_stop(char c)
{
	if (c == '0' || c == '1' || is_player(c))
		return (1);
	return (0);
}

int	check_surroundings(t_cube *cube, char *line, int x, int y)
{
	int	len;

	len = ft_strlen(line);
	if (x == 0)
		return (1);
	if (x == len - 1)
		return (1);
	if ((int)ft_strlen(cube->map[y - 1]) - 1 < x || !is_valid_stop(cube->map[y - 1][x]))
		return (1);
	if ((int)ft_strlen(cube->map[y + 1]) - 1 < x || !is_valid_stop(cube->map[y + 1][x]))
		return (1);
	if (!is_valid_stop(line[x - 1]) || !is_valid_stop(line[x + 1]))
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

int	first_last_line(t_cube *cube)
{
	int	i;
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
	int	i;
	int	len;
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

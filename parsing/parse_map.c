#include "../cub3D.h"

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

int	check_surroundings(t_cube *cube, char *line, int x, int y)
{
	int	len;

	len = ft_strlen(line);
	if (x == 0)
		return (1);
	if (x == len - 1)
		return (1);
	if ((int)ft_strlen(cube->map[y - 1]) - 1 < x
		|| !is_valid_stop(cube->map[y - 1][x]))
		return (1);
	if ((int)ft_strlen(cube->map[y + 1]) - 1 < x
		|| !is_valid_stop(cube->map[y + 1][x]))
		return (1);
	if (!is_valid_stop(line[x - 1]) || !is_valid_stop(line[x + 1]))
		return (1);
	return (0);
}

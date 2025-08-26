/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:37:28 by motelti           #+#    #+#             */
/*   Updated: 2025/07/18 19:13:47 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	validate_file_extension(char *name)
{
	int	i;

	i = 0;
	if (name == NULL)
		return (1);
	while (name[i])
		i++;
	if (i <= 4)
		return (extension_err(), 1);
	i = i - 4;
	if (ft_strcmp(name + i, ".cub") != 0)
		return (extension_err(), 1);
	return (0);
}

int	set_param(t_cube *cube, char *line, int *n)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3))
	{
		if (set_no_so(cube, line, n) == 1)
			return (1);
	}
	else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		if (set_we_ea(cube, line, n) == 1)
			return (1);
	}
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (set_f_c(cube, line, n) == 1)
			return (1);
	}
	else if (is_all_space(line))
		return (0);
	else
		return (1);
	return (0);
}

int	param_check(t_cube *cube, int fd)
{
	int		params;
	char	*line;

	params = 6;
	while (params)
	{
		line = rm_newline(get_next_line(fd));
		if (line == NULL || set_param(cube, line, &params))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

t_cube	*validate_file(int fd)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (cube == NULL)
		return (NULL);
	init_cube(cube);
	if (param_check(cube, fd))
		return (free_cube(cube), close(fd), NULL);
	if (parse_map(cube, fd))
	{
		ft_putstr_fd("error: Invalid map\n", 2);
		return (free_cube(cube), close(fd), NULL);
	}
	close(fd);
	if (map_check(cube))
	{
		ft_putstr_fd("error: Invalid map\n", 2);
		return (free_cube(cube), NULL);
	}
	return (cube);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:37:28 by motelti           #+#    #+#             */
/*   Updated: 2025/07/15 00:20:00 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extension_err(void)
{
	ft_putstr_fd("error: invalid file extension!\n", 2);
}

void	cant_open_err(void)
{
	ft_putstr_fd("error: can't open the file!\n", 2);
}

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

void	init_cube(t_cube *cube)
{
	cube->no = NULL;
	cube->so = NULL;
	cube->we = NULL;
	cube->ea = NULL;
	cube->map = NULL;
}

int	set_param(char *line, int *n)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		cube->no = get_rest_line(line);
		if (cube->no == NULL)
			return (1);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		cube->no = get_rest_line(line);
		if (cube->no == NULL)
			return (1);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		cube->no = get_rest_line(line);
		if (cube->no == NULL)
			return (1);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		cube->no = get_rest_line(line);
		if (cube->no == NULL)
			return (1);
	}
	return (0);
}

int	param_check(t_cube *cube, int fd)
{
	int		params;
	char	*line;

	params = 4;
	while (params)
	{
		line = get_next_line(fd);
		if (line == NULL || set_param(line, &param))
			return (1);
	}

}

t_cube	*validate_file(int fd)
{
	//close fd on error
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (cube == NULL)
		return (NULL);
	init_cube(cube);
	if (param_check(cube, fd))
		return (NULL); //must close fd and free cube
	//map_check(cube, fd);
}

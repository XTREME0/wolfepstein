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

int	set_no_so(t_cube *cube, char *line, int *n)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		cube->no = get_rest_line(line);
		if (cube->no == NULL)
			return (1);
		printf("NO -> %s\n", cube->no);//dlt
		*n = *n + 1;
		return (0);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		cube->so = get_rest_line(line);
		if (cube->so == NULL)
			return (1);
		printf("SO -> %s\n", cube->so);//dlt
		*n = *n + 1;
		return (0);
	}
	return (2);
}

int	set_we_ea(t_cube *cube, char *line, int *n)
{
	if (!ft_strncmp(line, "WE ", 3))
	{
		cube->we = get_rest_line(line);
		if (cube->we == NULL)
			return (1);
		printf("WE -> %s\n", cube->we);//dlt
		*n = *n + 1;
		return (0);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		cube->ea = get_rest_line(line);
		if (cube->ea == NULL)
			return (1);
		printf("EA -> %s\n", cube->ea);//dlt
		*n = *n + 1;
		return (0);
	}
	return (2);
}

int	set_f_c(char *line, int *n)
{
	//tmp bs:
	if (line == NULL && *n == 0)
		return (9999);
	return (1);
}

int	is_all_space(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_rest_line(char *line)
{
	char **sections;
	char	*rest;
	int		tmp;

	sections = ft_split(line, ' ');
	if (sections == NULL || sections[1] == NULL || sections[2] != NULL)
	{
		free_tab(sections);
		return (NULL);
	}
	rest = sections[1];
	free(sections[0]);
	free(sections);
	printf("that section is %s\n", rest);
	tmp = open(rest, O_RDONLY, 0444);
	if (tmp == -1)
	{
		free(rest);
		ft_putstr_fd("error: can't find texture\n", 2);
		return (NULL);
	}
	close(tmp);
	return (rest);
}

int	set_param(t_cube *cube, char *line, int *n)
{
	if ((!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3))
			&& set_no_so(cube, line, n) == 1)
		return (1);
	else if ((!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
			&& set_we_ea(cube, line, n) == 1)
		return (1);
	else if ((!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			&& set_f_c(line, n) == 1)
		return (1);
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

	params = 4;
	while (params)
	{
		line = get_next_line(fd);
		if (line == NULL || set_param(cube, line, &params))
		{
			free(line);
			return (1);
		}
	}
	return (0);
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
	return (cube);
}

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
	cube->c = -1;
	cube->f = -1;
	cube->map = NULL;
}

int	set_no_so(t_cube *cube, char *line, int *n)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (cube->no != NULL)
			return (1);
		cube->no = get_rest_line(line, 1);
		if (cube->no == NULL)
			return (1);
		*n = *n - 1;
		return (0);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (cube->so != NULL)
			return (1);
		cube->so = get_rest_line(line, 1);
		if (cube->so == NULL)
			return (1);
		*n = *n - 1;
		return (0);
	}
	return (2);
}

int	set_we_ea(t_cube *cube, char *line, int *n)
{
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (cube->we != NULL)
			return (1);
		cube->we = get_rest_line(line, 1);
		if (cube->we == NULL)
			return (1);
		*n = *n - 1;
		return (0);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (cube->ea != NULL)
			return (1);
		cube->ea = get_rest_line(line, 1);
		if (cube->ea == NULL)
			return (1);
		*n = *n - 1;
		return (0);
	}
	return (2);
}

int	set_f_c(t_cube *cube, char *line, int *n)
{
	if (!ft_strncmp(line, "F ", 2))
	{
		if (cube->f != -1)
			return (1);
		cube->f = get_color(line);
		if (cube->f == -1)
			return (1);
		*n = *n - 1;
		return (0);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		if (cube->c != -1)
			return (1);
		cube->c = get_color(line);
		if (cube->c == -1)
			return (1);
		*n = *n - 1;
		return (0);
	}
	return (2);
}

int	is_all_space(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] != ' ')
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

char	*rm_newline(char *str)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return(str);
}

double	convert_rgb(char **section)
{
	int		i;
	int		j;
	int r;
	int g;
	int b;

	i = 0;
	while (section[i])
	{
		j = 0;
		if (ft_strlen(section[i]) > 3 || (ft_strlen(section[i]) == 3 && ft_strcmp(section[i], "255") > 0))
			return (free_tab(section), -1);
		while (section[i][j])
		{
			if (!ft_isdigit(section[i][j]))
				return (free_tab(section), -1);
			j++;
		}
		i++;
	}
	r = ft_atoi(section[0]);
	g = ft_atoi(section[1]);
	b = ft_atoi(section[2]);
	return (free_tab(section), (double)((r << 16) | (g << 8) | b));
}

double	get_color(char *line)
{
	char	*l;
	char	**sections;

	l = get_rest_line(line, 0);
	if (l == NULL)
		return (-1);
	sections = ft_split(l, ',');
	if (sections == NULL)
		return (-1);
	if (!sections[0] || !sections[1] || !sections[2] || sections[3])
	{
		free_tab(sections);
		return (-1);
	}
	return (convert_rgb(sections));
}

char	*get_rest_line(char *line, int flag)
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
	if (flag)
	{
		tmp = open(rest, O_RDONLY, 0444);
		if (tmp == -1)
		{
			free(rest);
			ft_putstr_fd("error: can't find texture\n", 2);
			return (NULL);
		}
		close(tmp);
	}
	return (rest);
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

void	free_cube(t_cube *cube)
{
	free(cube->no);
	free(cube->so);
	free(cube->we);
	free(cube->ea);
	free_tab(cube->map);
	free(cube);
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

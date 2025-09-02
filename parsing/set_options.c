#include "../cub3D.h"

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

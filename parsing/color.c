#include "../cub3D.h"

long	convert_rgb(char **section)
{
	int		i;
	int		j;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (section[i])
	{
		j = 0;
		if (ft_strlen(section[i]) > 3 || (ft_strlen(section[i]) == 3
				&& ft_strcmp(section[i], "255") > 0))
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
	return (free_tab(section), ((r << 16) | (g << 8) | b));
}

long	get_color(char *line)
{
	char	*l;
	char	**sections;

	l = get_rest_line(line, 0);
	if (l == NULL)
		return (-1);
	sections = ft_split(l, ',');
	free(l);
	if (sections == NULL)
		return (-1);
	if (!sections[0] || !sections[1] || !sections[2] || sections[3])
	{
		free_tab(sections);
		return (-1);
	}
	return (convert_rgb(sections));
}

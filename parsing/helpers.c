#include "../cub3D.h"

int	is_all_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
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
	return (str);
}

char	*get_rest_line(char *line, int flag)
{
	char	**sections;
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

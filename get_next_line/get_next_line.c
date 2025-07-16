/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataai <ataai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:03:14 by ataai             #+#    #+#             */
/*   Updated: 2024/12/05 13:03:16 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	fill_line(char **buff, char **line)
{
	char		**tab;

	if (ft_strchr(*buff, '\n') == NULL)
	{
		*line = fake_join(*line, *buff);
		*buff = NULL;
		if (*line == NULL)
			return (1);
		return (2);
	}
	else
	{
		tab = fake_split(*buff);
		if (tab == NULL)
			return (free(*buff), *buff = NULL, free(*line), 1);
		*line = fake_join(*line, tab[0]);
		if (*line == NULL)
			return (free(*buff), *buff = NULL, free(tab[1]), free(tab), 1);
		return (free(*buff), *buff = tab[1], free(tab), 0);
	}
}

static char	*liriri_gnl(char *line, int n, int fd)
{
	static char	*buff;

	while (1)
	{
		if (buff == NULL)
		{
			buff = malloc((size_t)BUFFER_SIZE + 1);
			if (buff == NULL)
				return (NULL);
			n = read(fd, buff, BUFFER_SIZE);
			if (n == 0)
				return (free(buff), buff = NULL, line);
			if (n < 0)
				return (free(buff), buff = NULL, free(line), NULL);
			buff[n] = '\0';
		}
		else
		{
			n = fill_line(&buff, &line);
			if (n == 1)
				return (NULL);
			else if (n == 0)
				return (line);
		}
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	int			n;

	line = NULL;
	return (liriri_gnl(line, n = 0, fd));
}

char	*fake_join(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (str = ft_strdup(s2), free(s2), str);
	if (s2 == NULL)
		return (str = ft_strdup(s1), free(s1), str);
	str = fake_strcat(s1, s2);
	if (str == NULL)
		return (free(s1), free(s2), NULL);
	return (free(s1), free(s2), str);
}

char	**fake_split(char *str)
{
	size_t	i;
	char	**tab;
	char	*ptr;

	if (str == NULL)
		return (NULL);
	tab = malloc(2 * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	ptr = ft_strchr(str, '\n') + 1;
	tab[0] = ft_substr(str, 0, ptr - str);
	if (*ptr == '\0')
		return (tab[1] = NULL, tab);
	tab[1] = ft_strdup(ptr);
	return (tab);
}

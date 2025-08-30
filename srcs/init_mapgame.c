/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mapgame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:40:16 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 11:03:53 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	set_map_dimensions(t_game *game, t_cube *cube)
{
	int	i;
	int	len;

	game->map_rows = tab_len(cube->map);
	game->map_cols = 0;
	i = 0;
	while (cube->map[i])
	{
		len = ft_strlen(cube->map[i]);
		if (len > game->map_cols)
			game->map_cols = len;
		i++;
	}
}

static void	free_failed_map(t_game *game, int i)
{
	while (--i >= 0)
		free(game->map[i]);
	free(game->map);
}

static int	copy_map(t_game *game, t_cube *cube)
{
	int	i;

	game->map = malloc(game->map_rows * sizeof(char *));
	if (!game->map)
		return (1);
	i = 0;
	while (i < game->map_rows)
	{
		game->map[i] = ft_strdup(cube->map[i]);
		if (!game->map[i])
			return (free_failed_map(game, i), 1);
		i++;
	}
	return (0);
}

int	allocate_textures_map(int *i, t_game *game, t_cube *cube)
{
	game->no_texture = ft_strdup(cube->no);
	game->so_texture = ft_strdup(cube->so);
	game->we_texture = ft_strdup(cube->we);
	game->ea_texture = ft_strdup(cube->ea);
	if (!game->no_texture || !game->so_texture
		|| !game->we_texture || !game->ea_texture)
	{
		free(game->no_texture);
		free(game->so_texture);
		free(game->we_texture);
		free(game->ea_texture);
		i = 0;
		while (*i < game->map_rows)
		{
			free(game->map[*i]);
			i++;
		}
		return (free(game->map), 1);
	}
	game->floor_color = cube->f;
	game->ceiling_color = cube->c;
	return (1);
}

int	init_game(t_game *game, t_cube *cube)
{
	set_map_dimensions(game, cube);
	if (copy_map(game, cube))
		return (1);
	if (!allocate_textures_map(&(int){0}, game, cube))
		return (0);
	init_player(game);
	return (0);
}

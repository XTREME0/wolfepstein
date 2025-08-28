/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:33:10 by motelti           #+#    #+#             */
/*   Updated: 2025/08/28 11:59:55 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	fill_north(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = -1;
	game->plane_x = 0.66;
	game->plane_y = 0;
}

static void	set_player_direction(t_game *game, char dir)
{
	if (dir == 'N')
		fill_north(game);
	else if (dir == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
	else if (dir == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
}

static int	find_player(t_game *game, int y)
{
	int	x;

	x = 0;
	while (game->map[y][x])
	{
		if (is_player(game->map[y][x]))
		{
			game->player_x = x + 0.5;
			game->player_y = y + 0.5;
			set_player_direction(game, game->map[y][x]);
			game->map[y][x] = '0';
			return (1);
		}
		x++;
	}
	return (0);
}

void	init_player(t_game *game)
{
	int	y;

	y = 0;
	while (game->map[y])
	{
		if (find_player(game, y))
			return ;
		y++;
	}
}

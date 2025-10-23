/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:29:51 by motelti           #+#    #+#             */
/*   Updated: 2025/10/23 23:26:13 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	handle_exit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

static void	handle_move(t_game *game, double move_speed, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + dir * game->dir_x * move_speed;
	new_y = game->player_y + dir * game->dir_y * move_speed;
	if (new_x >= 0 && new_x < game->map_cols && new_y >= 0
		&& new_y < game->map_rows && game->map[(int)new_y][(int)new_x] == '0')
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
}

static void	handle_left_right(t_game *game, double move_speed, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + dir * game->plane_x * move_speed;
	new_y = game->player_y + dir * game->plane_y * move_speed;
	if (new_x >= 0 && new_x < game->map_cols && new_y >= 0
		&& new_y < game->map_rows && game->map[(int)new_y][(int)new_x] == '0')
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
}

static void	handle_rotate(t_game *game, double rot_speed, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	c;
	double	s;

	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	c = cos(dir * rot_speed);
	s = sin(dir * rot_speed);
	game->dir_x = game->dir_x * c - game->dir_y * s;
	game->dir_y = old_dir_x * s + game->dir_y * c;
	game->plane_x = game->plane_x * c - game->plane_y * s;
	game->plane_y = old_plane_x * s + game->plane_y * c;
}

int	key_press(int keycode, void *param)
{
	t_game	*game;
	double	move_speed;
	double	rot_speed;

	game = (t_game *)param;
	move_speed = 0.5;
	rot_speed = 0.05;
	if (keycode == KEY_ESC)
		handle_exit(game);
	else if (keycode == KEY_W)
		handle_move(game, move_speed, 1);
	else if (keycode == KEY_S)
		handle_move(game, move_speed, -1);
	else if (keycode == KEY_A)
		handle_left_right(game, move_speed, -1);
	else if (keycode == KEY_D)
		handle_left_right(game, move_speed, 1);
	else if (keycode == KEY_RIGHT)
		handle_rotate(game, rot_speed, 1);
	else if (keycode == KEY_LEFT)
		handle_rotate(game, rot_speed, -1);
	return (0);
}

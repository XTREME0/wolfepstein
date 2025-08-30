/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:29:46 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 10:52:27 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_textures(t_game *game)
{
	free(game->no_texture);
	free(game->so_texture);
	free(game->we_texture);
	free(game->ea_texture);
}

void	handle_exit1(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	if (game->map)
	{
		while (i < game->map_rows)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	destroy_textures(game);
	if (game->no_img)
		mlx_destroy_image(game->mlx, game->no_img);
	if (game->so_img)
		mlx_destroy_image(game->mlx, game->so_img);
	if (game->we_img)
		mlx_destroy_image(game->mlx, game->we_img);
	if (game->ea_img)
		mlx_destroy_image(game->mlx, game->ea_img);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_cube	*cube;

	ft_memset(&game, 0, sizeof(game));
	if (init_game_data(&game, &cube, argc, argv))
		return (1);
	if (load_and_check_textures(&game))
		return (1);
	if (create_window_and_image(&game))
		return (1);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_loop(game.mlx);
	return (handle_exit1(&game), 0);
}

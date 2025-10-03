/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_win_tex2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataai <ataai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:07:14 by ataai             #+#    #+#             */
/*   Updated: 2025/10/03 17:08:14 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	load_and_check_textures(t_game *game)
{
	if (check_texture_validity(game))
	{
		ft_putstr_fd("error: failed to load textures\n", 2);
		return (handle_exit1(game), 1);
	}
	if (textures(game))
	{
		ft_putstr_fd("error: failed to load textures\n", 2);
		return (handle_exit1(game), 1);
	}
	if (check_for_errors(game))
	{
		ft_putstr_fd("error: failed to load textures\n", 2);
		return (handle_exit1(game), 1);
	}
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_exit1(game);
	return (0);
}

int	create_window_and_image(t_game *game)
{
	game->win = mlx_new_window(game->mlx, \
		WINDOW_WIDTH, WINDOW_HEIGHT, "WOLFEPSTEIN");
	if (!game->win)
		return (handle_exit1(game), 1);
	mlx_hook(game->win, 17, 0, close_window, game);
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, \
			&game->img.line_length, &game->img.endian);
	return (0);
}

int	check_for_errors(t_game *game)
{
	if (!game->no_img || !game->so_img || !game->we_img || !game->ea_img)
		return (1);
	return (0);
}

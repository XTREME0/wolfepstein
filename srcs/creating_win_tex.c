/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_win_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:50:25 by motelti           #+#    #+#             */
/*   Updated: 2025/08/28 10:36:53 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	textures(t_game *game)
{
	int		width;
	int		height;
	int		dummy;

	width = 0;
	height = 0;
	dummy = 0;
	game->no_img = mlx_xpm_file_to_image(game->mlx, \
			game->no_texture, &width, &height);
	game->so_img = mlx_xpm_file_to_image(game->mlx, \
			game->so_texture, &width, &height);
	game->we_img = mlx_xpm_file_to_image(game->mlx, \
			game->we_texture, &width, &height);
	game->ea_img = mlx_xpm_file_to_image(game->mlx, \
			game->ea_texture, &width, &height);
	game->tex_width = width;
	game->tex_height = height;
	game->no_addr = mlx_get_data_addr(game->no_img, &width, &height, &dummy);
	game->so_addr = mlx_get_data_addr(game->so_img, &width, &height, &dummy);
	game->we_addr = mlx_get_data_addr(game->we_img, &width, &height, &dummy);
	game->ea_addr = mlx_get_data_addr(game->ea_img, &width, &height, &dummy);
}

int	init_game_data(t_game *game, t_cube **cube, int ac, char **av)
{
	*cube = cube_parsing(ac, av);
	if (!*cube)
		return (1);
	if (init_game(game, *cube))
		return (free_cube(*cube), 1);
	free_cube(*cube);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (handle_exit1(game), 1);
	return (0);
}

int	load_and_check_textures(t_game *game)
{
	textures(game);
	if (!game->no_img || !game->so_img || !game->we_img || !game->ea_img)
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
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (handle_exit1(game), 1);
	mlx_hook(game->win, 17, 0, close_window, game);
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, \
			&game->img.line_length, &game->img.endian);
	return (0);
}

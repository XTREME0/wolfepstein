/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_win_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:50:25 by motelti           #+#    #+#             */
/*   Updated: 2025/09/05 14:05:36 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int get_textures_data_addr(t_game *game)
{
	int		dummy;

	game->no_addr = mlx_get_data_addr(game->no_img, &dummy, &dummy, &dummy);
	if (!game->no_addr)
		return (1);
	game->so_addr = mlx_get_data_addr(game->so_img, &dummy, &dummy, &dummy);
	if (!game->so_addr)
		return (1);
	game->we_addr = mlx_get_data_addr(game->we_img, &dummy, &dummy, &dummy);
	if (!game->we_addr)
		return (1);
	game->ea_addr = mlx_get_data_addr(game->ea_img, &dummy, &dummy, &dummy);
	if (!game->ea_addr)
		return (1);
	return (0);
}

void	init_texteres_dimensions(t_game *game, t_xpm xpm)
{
	game->no_tex_width = xpm.no_width;
	game->no_tex_height = xpm.no_height;
	game->so_tex_width = xpm.so_width;
	game->so_tex_height = xpm.so_height;
	game->we_tex_width = xpm.we_width;
	game->we_tex_height = xpm.we_height;
	game->ea_tex_width = xpm.ea_width;
	game->ea_tex_height = xpm.ea_height;
}

int    textures(t_game *game)
{
	int		dummy;
	t_xpm	xpm;

	game->no_img = mlx_xpm_file_to_image(game->mlx, game->no_texture, \
			&xpm.no_width, &xpm.no_height);
	game->so_img = mlx_xpm_file_to_image(game->mlx, game->so_texture, \
			&xpm.so_width, &xpm.so_height);
	game->we_img = mlx_xpm_file_to_image(game->mlx, game->we_texture, \
			&xpm.we_width, &xpm.we_height);
	game->ea_img = mlx_xpm_file_to_image(game->mlx, game->ea_texture, \
			&xpm.ea_width, &xpm.ea_height);
	if (check_for_errors(game))
		return (1);
	init_texteres_dimensions(game, xpm);
	// if (!get_textures_data_addr(game))
	// 	return (1);
	game->no_addr = mlx_get_data_addr(game->no_img, &dummy, &dummy, &dummy);
	if (!game->no_addr)
		return (1);
	game->so_addr = mlx_get_data_addr(game->so_img, &dummy, &dummy, &dummy);
	if (!game->so_addr)
		return (1);
	game->we_addr = mlx_get_data_addr(game->we_img, &dummy, &dummy, &dummy);
	if (!game->we_addr)
		return (1);
	game->ea_addr = mlx_get_data_addr(game->ea_img, &dummy, &dummy, &dummy);
	if (!game->ea_addr)
		return (1);
	return (0);
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

int	check_texture_validity(t_game *game)
{
	if (!game->no_texture || !game->so_texture || !game->we_texture || !game->ea_texture)
		return (1);
	return (0);
}

int	check_for_errors(t_game *game)
{
	if (!game->no_img || !game->so_img || !game->we_img || !game->ea_img)
		return (1);
	return (0);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_win_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataai <ataai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:50:25 by motelti           #+#    #+#             */
/*   Updated: 2025/10/03 17:08:17 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_textures_data_addr(t_game *game)
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

int	textures(t_game *game)
{
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
	if (get_textures_data_addr(game) == 1)
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
	if (!game->no_texture || !game->so_texture
		|| !game->we_texture || !game->ea_texture)
		return (1);
	return (0);
}

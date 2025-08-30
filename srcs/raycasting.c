/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:06:47 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 11:06:24 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_vertical_line(t_game *game, int x, t_render_params draw)
{
	int	y;

	y = 0;
	while (y < draw.draw_start)
		set_pixel(&game->img, x, y++, game->ceiling_color);
	y = draw.draw_start;
	while (y < draw.draw_end)
		set_pixel(&game->img, x, y++, draw.color);
	while (y < WINDOW_HEIGHT)
		set_pixel(&game->img, x, y++, game->floor_color);
}

static double	calc_delta(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	else
		return (fabs(1 / ray_dir));
}

void	init_ray_map(t_game *game, t_ray *r)
{
	r->map_x = (int)game->player_x;
	r->map_y = (int)game->player_y;
	r->delta_dist_x = calc_delta(r->ray_dir_x);
	r->delta_dist_y = calc_delta(r->ray_dir_y);
}

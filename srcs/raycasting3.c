/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:02:46 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 11:02:49 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	perform_dda(t_game *game, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= game->map_cols
			|| r->map_y < 0 || r->map_y >= game->map_rows
			|| game->map[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

void	init_ray_params(t_game *game, int x, t_render_params *p)
{
	p->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	p->ray_dir_x = game->dir_x + game->plane_x * p->camera_x;
	p->ray_dir_y = game->dir_y + game->plane_y * p->camera_x;
}

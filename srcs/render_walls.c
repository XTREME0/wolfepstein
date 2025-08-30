/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:08:40 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 10:47:16 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_render_params(t_game *game, t_ray *r, t_render_params *p)
{
	p->camera_x = 0.0;
	p->ray_dir_x = 0.0;
	p->ray_dir_y = 0.0;
	p->line_height = 0;
	p->draw_start = 0;
	p->draw_end = 0;
	p->texture_img = NULL;
	p->texture_addr = NULL;
	init_ray_params(game, r->x, p);
	r->ray_dir_x = p->ray_dir_x;
	r->ray_dir_y = p->ray_dir_y;
	init_ray_map(game, r);
	calc_step_and_sidedist(game, p, r);
	perform_dda(game, r);
	calc_wall_properties(r, p);
}

static void	not_side_ray(t_game *game, t_render_params *p)
{
	if (p->ray_dir_y > 0)
	{
		p->texture_img = game->so_img;
		p->texture_addr = game->so_addr;
	}
	else
	{
		p->texture_img = game->no_img;
		p->texture_addr = game->no_addr;
	}
}

void	select_texture(t_game *game, t_ray *r, t_render_params *p)
{
	if (r->side == 0)
	{
		if (p->ray_dir_x > 0)
		{
			p->texture_img = game->we_img;
			p->texture_addr = game->we_addr;
		}
		else
		{
			p->texture_img = game->ea_img;
			p->texture_addr = game->ea_addr;
		}
	}
	else
		not_side_ray(game, p);
}

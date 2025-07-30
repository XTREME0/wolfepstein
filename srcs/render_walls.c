/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:08:40 by motelti           #+#    #+#             */
/*   Updated: 2025/07/19 14:36:29 by motelti          ###   ########.fr       */
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
	init_ray_params(game, r->x, &p->camera_x, &p->ray_dir_x, &p->ray_dir_y);
	r->ray_dir_x = p->ray_dir_x;
	r->ray_dir_y = p->ray_dir_y;
	init_ray_map(game, r);
	calc_step_and_sidedist(game, p->ray_dir_x, p->ray_dir_y, r);
	perform_dda(game, r);
	calc_wall_properties(r, &p->line_height, &p->draw_start, &p->draw_end);
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
}

void	calc_tex_x(t_game *game, t_ray *r, t_render_params *p)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = game->player_y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = game->player_x + r->perp_wall_dist * r->ray_dir_x;

	wall_x -= (int)wall_x;
	p->tex_x = (int)(wall_x * game->tex_width);

	if (r->side == 0 && p->ray_dir_x > 0)
		p->tex_x = game->tex_width - p->tex_x - 1;
	if (r->side != 0 && p->ray_dir_y < 0)
		p->tex_x = game->tex_width - p->tex_x - 1;
}

void	draw_textured_line(t_game *game, t_ray *r, t_render_params *p)
{
	int	y;

	y = p->draw_start;
	while (y < p->draw_end)
	{
		int tex_y = (int)((y - (WINDOW_HEIGHT - p->line_height) / 2) * game->tex_height / p->line_height);
		
		p->color = *(unsigned int *)(p->texture_addr + (tex_y * game->tex_width + p->tex_x) * 4);
		set_pixel(&game->img, r->x, y, p->color);
		y++;
	}
}

void	render_column(t_game *game, t_ray *r)
{
	t_render_params	p;

	init_render_params(game, r, &p);
	select_texture(game, r, &p);
	calc_tex_x(game, r, &p);
	draw_vertical_line(game, r->x, p.draw_start, p.draw_end, p.color);
	draw_textured_line(game, r, &p);
}

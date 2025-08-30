/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:02:58 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 11:03:00 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	int	tex_y;

	y = p->draw_start;
	while (y < p->draw_end)
	{
		tex_y = (int)((y - (WINDOW_HEIGHT - p->line_height) / 2) \
				* game->tex_height / p->line_height);
		p->color = *(unsigned int *)(p->texture_addr + (tex_y \
					* game->tex_width + p->tex_x) * 4);
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
	draw_vertical_line(game, r->x, p);
	draw_textured_line(game, r, &p);
}

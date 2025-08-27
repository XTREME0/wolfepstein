/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:06:47 by motelti           #+#    #+#             */
/*   Updated: 2025/07/19 14:36:38 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	clear_screen(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			set_pixel(&game->img, x, y, 0);
			x++;
		}
		y++;
	}
}

static void	init_ray(t_game *game, int x, double *camera_x,
		double *ray_dir_x, double *ray_dir_y)
{
	*camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	*ray_dir_x = game->dir_x + game->plane_x * (*camera_x);
	*ray_dir_y = game->dir_y + game->plane_y * (*camera_x);
}

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

void draw_vertical_line(t_game *game, int x, int draw_start, int draw_end, int color)
{
	int y;

	y = 0;
	while (y < draw_start)
		set_pixel(&game->img, x, y++, game->ceiling_color); // Use ceiling color
	y = draw_start;
	while (y < draw_end)
		set_pixel(&game->img, x, y++, color); // Wall color
	while (y < WINDOW_HEIGHT)
		set_pixel(&game->img, x, y++, game->floor_color); // Use floor color
}

static double	calc_delta(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	else
		return (fabs(1 / ray_dir));
}

void	calc_step_and_sidedist(t_game *game, double ray_dir_x, double ray_dir_y, t_ray *r)
{
	if (ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->player_x) * r->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->player_y) * r->delta_dist_y;
	}
}

void init_ray_params(t_game *game, int x, double *camera_x, double *ray_dir_x, double *ray_dir_y)
{
	*camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	*ray_dir_x = game->dir_x + game->plane_x * *camera_x;
	*ray_dir_y = game->dir_y + game->plane_y * *camera_x;
}

void init_ray_map(t_game *game, t_ray *r)
{
	r->map_x = (int)game->player_x;
	r->map_y = (int)game->player_y;
	r->delta_dist_x = calc_delta(r->ray_dir_x);
	r->delta_dist_y = calc_delta(r->ray_dir_y);
}

void calc_wall_properties(t_ray *r, int *line_height, int *draw_start, int *draw_end)
{
	double perp_wall_dist = 0.0;
	if (r->side == 0)
	{
		perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	}
	else
	{
		perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	}
	r->perp_wall_dist = perp_wall_dist;
	*line_height = (int)(WINDOW_HEIGHT / r->perp_wall_dist);
	*draw_start = -(*line_height) / 2 + WINDOW_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
}

int	render_frame(void *param)
{
	t_game	*game;
	t_ray	r;

	game = (t_game *)param;
	clear_screen(game);
	r.x = 0;
	while (r.x < WINDOW_WIDTH)
	{
		render_column(game, &r);
		r.x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

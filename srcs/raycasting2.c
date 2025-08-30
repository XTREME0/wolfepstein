#include "../cub3D.h"

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

void	calc_wall_properties(t_ray *r, int *l_height, int *d_start, int *d_end)
{
	double	perp_wall_dist;

	perp_wall_dist = 0.0;
	if (r->side == 0)
	{
		perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	}
	else
	{
		perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	}
	r->perp_wall_dist = perp_wall_dist;
	*l_height = (int)(WINDOW_HEIGHT / r->perp_wall_dist);
	*d_start = -(*l_height) / 2 + WINDOW_HEIGHT / 2;
	if (*d_start < 0)
		*d_start = 0;
	*d_end = *l_height / 2 + WINDOW_HEIGHT / 2;
	if (*d_end >= WINDOW_HEIGHT)
		*d_end = WINDOW_HEIGHT - 1;
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

void	calc_step_and_sidedist(t_game *game,  t_render_params *p, t_ray *r)
{
	if (p->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->player_x) * r->delta_dist_x;
	}
	if (p->ray_dir_y < 0)
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

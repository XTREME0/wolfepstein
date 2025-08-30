/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:33:51 by motelti           #+#    #+#             */
/*   Updated: 2025/08/30 10:47:12 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define KEY_W 13  // keycode for 'W'
# define KEY_S 1   // keycode for 'S'
# define KEY_A 0   // keycode for 'A'
# define KEY_D 2   // keycode for 'D'
# define KEY_ESC 53 // keycode for 'Escape'
# define KEY_LEFT 123  // keycode for left arrow
# define KEY_RIGHT 124 // keycode for right arrow

typedef struct s_cube
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned int	f;
	unsigned int	c;
	char			**map;
	int				x_max;
	int				y_max;
}	t_cube;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_data		img;
	char		**map;
	int			map_rows;
	int			map_cols;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	long long	floor_color;
	long long	ceiling_color;
	void		*no_img;
	void		*so_img;
	void		*we_img;
	void		*ea_img;
	char		*no_addr;
	char		*so_addr;
	char		*we_addr;
	char		*ea_addr;
	int			tex_width;
	int			tex_height;
}	t_game;

typedef struct s_ray
{
	int		x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_render_params
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	void	*texture_img;
	char	*texture_addr;
	int		tex_x;
	int		color;
}	t_render_params;

// =========================================> ray-castnig
void	draw_vertical_line(t_game *game, int x, t_render_params draw);
void	init_ray_params(t_game *game, int x, t_render_params *p);
void	init_ray_map(t_game *game, t_ray *r);
void	calc_step_and_sidedist(t_game *game, t_render_params *p, t_ray *r);
void	calc_wall_properties(t_ray *r, t_render_params *p);
void	perform_dda(t_game *game, t_ray *r);
void	render_column(t_game *game, t_ray *r);
int		render_frame(void *param);
int		key_press(int keycode, void *param);
void	init_player(t_game *game);
int		init_game(t_game *game, t_cube *cube);
void	textures(t_game *game);
int		init_game_data(t_game *game, t_cube **cube, int ac, char **av);
int		load_and_check_textures(t_game *game);
int		create_window_and_image(t_game *game);
void	handle_exit1(t_game *game);
void	set_pixel(t_data *img, int x, int y, int color);
void	init_render_params(t_game *game, t_ray *r, t_render_params *p);
void	select_texture(t_game *game, t_ray *r, t_render_params *p);

// =========================================> parsing
void	extension_err(void);
int		validate_file_extension(char *name);
t_cube	*validate_file(int fd);
t_cube	*cube_parsing(int argc, char **argv);
void	cant_open_err(void);
int		param_check(t_cube *cube, int fd);
int		set_param(t_cube *cube, char *line, int *n);
int		is_all_space(char *line);
int		set_f_c(t_cube *cube, char *line, int *n);
int		set_we_ea(t_cube *cube, char *line, int *n);
int		set_no_so(t_cube *cube, char *line, int *n);
void	init_cube(t_cube *cube);
char	*get_rest_line(char *line, int flag);
void	free_tab(char **tab);
long	get_color(char *line);
long	convert_rgb(char **section);
char	*rm_newline(char *str);
int		parse_map(t_cube *cube, int fd);
int		map_check(t_cube *cube);
int		mid_line(t_cube *cube, int y);
int		first_last_line(t_cube *cube);
int		is_player(char c);
int		check_surroundings(t_cube *cube, char *line, int x, int y);
int		is_valid_stop(char c);
int		check_map_line(char *line);
int		banned_char(char c);
int		tab_join(t_cube *cube, char *line);
int		tab_len(char **tab);
void	free_cube(t_cube *cube);

#endif

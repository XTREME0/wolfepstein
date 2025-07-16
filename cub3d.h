/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:32:42 by motelti           #+#    #+#             */
/*   Updated: 2025/07/14 23:09:55 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
#include <fcntl.h>

// ---------------------------------------------------------> t_cube
typedef struct s_cube
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	long long	f;
	long long	c;
	char	**map;
	int		x_max;
	int		y_max;
} t_cube;

// ---------------------------------------------------------> parsing
void	extension_err(void);
int		validate_file_extension(char *name);
t_cube	*validate_file(int fd);
t_cube	*cube_parsing(int argc, char **argv);
void	cant_open_err(void);
int	param_check(t_cube *cube, int fd);
int	set_param(t_cube *cube, char *line, int *n);
int	is_all_space(char *line);
int	set_f_c(t_cube *cube, char *line, int *n);
int	set_we_ea(t_cube *cube, char *line, int *n);
int	set_no_so(t_cube *cube, char *line, int *n);
void	init_cube(t_cube *cube);
char	*get_rest_line(char *line, int flag);
void	free_tab(char **tab);
double	get_color(char *line);
double	convert_rgb(char **section);
char	*rm_newline(char *str);
int	parse_map(t_cube *cube, int fd);

#endif

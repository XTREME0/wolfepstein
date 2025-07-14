/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:32:42 by motelti           #+#    #+#             */
/*   Updated: 2025/07/14 18:49:08 by motelti          ###   ########.fr       */
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

// ---------------------------------------------------------> parsing
void	extension_err(void);
int		validate_file_extension(char *name);

// ---------------------------------------------------------> t_cube
typedef struct s_cube
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	//f
	//c
	char	**map;
	int		x_max;
	int		y_max;
} t_cube;


#endif

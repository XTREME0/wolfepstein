/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:37:40 by motelti           #+#    #+#             */
/*   Updated: 2025/07/18 17:07:33 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_cube	*cube_parsing(int argc, char **argv)
{
	int		fd;
	t_cube	*cube;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./cub3D file.cub\n", 2);
		return (NULL);
	}
	if (validate_file_extension(argv[1]))
		return (NULL);
	fd = open(argv[1], O_RDONLY, 0444);
	if (fd == -1)
		return (cant_open_err(), NULL);
	cube = validate_file(fd);
	if (cube == NULL)
		ft_putstr_fd("Invalid map!\n", 2);
	return (cube);
}

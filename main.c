/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:36:53 by motelti           #+#    #+#             */
/*   Updated: 2025/07/14 19:44:50 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = cube_parsing(argc, argv);
	if (cube == NULL)
		return (1);
	printf("------------> no: %s\n", cube->no);
	printf("------------> so: %s\n", cube->so);
	printf("------------> we: %s\n", cube->we);
	printf("------------> ea: %s\n", cube->ea);
	printf("------------> f: %lld\n", cube->f);
	printf("------------> c: %lld\n", cube->c);
	return (0);
}

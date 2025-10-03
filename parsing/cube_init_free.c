/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataai <ataai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:57:12 by ataai             #+#    #+#             */
/*   Updated: 2025/10/03 16:57:13 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_cube(t_cube *cube)
{
	free(cube->no);
	free(cube->so);
	free(cube->we);
	free(cube->ea);
	free_tab(cube->map);
	free(cube);
}

void	init_cube(t_cube *cube)
{
	cube->no = NULL;
	cube->so = NULL;
	cube->we = NULL;
	cube->ea = NULL;
	cube->c = -1;
	cube->f = -1;
	cube->map = NULL;
}

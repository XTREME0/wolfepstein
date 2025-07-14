/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motelti <motelti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:37:28 by motelti           #+#    #+#             */
/*   Updated: 2025/07/14 18:37:30 by motelti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extension_err(void)
{
	ft_putstr_fd("error:\ninvalid file extension!\n", 2);
}

int	validate_file_extension(char *name)
{
	int	i;

	i = 0;
	if (name == NULL)
		return (1);
	while (name[i])
		i++;
	if (i <= 5)
		return (extension_err(), 1);
	i = i - 5;
	if (ft_strcmp(name + i, ".cube") != 0)
		return (extension_err(), 1);
	return (0);
}

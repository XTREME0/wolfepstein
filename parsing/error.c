/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataai <ataai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:57:16 by ataai             #+#    #+#             */
/*   Updated: 2025/10/03 16:57:17 by ataai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	extension_err(void)
{
	ft_putstr_fd("error: invalid file extension!\n", 2);
}

void	cant_open_err(void)
{
	ft_putstr_fd("error: can't open the file!\n", 2);
}

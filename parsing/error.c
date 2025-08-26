#include "../cub3D.h"

void	extension_err(void)
{
	ft_putstr_fd("error: invalid file extension!\n", 2);
}

void	cant_open_err(void)
{
	ft_putstr_fd("error: can't open the file!\n", 2);
}

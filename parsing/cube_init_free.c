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

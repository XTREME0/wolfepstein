#include "cube.h"

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = cube_parsing(argc, argv);
	if (cube == NULL)
		return (1);
}

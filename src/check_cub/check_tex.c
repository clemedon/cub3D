#include "cube.h"

/*
 ** @brief      Check texture specs value.
 **
 ** - has to be a valid readable file
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_check_tex_value(const char *specs)
{
	int	fd;

	fd = open (specs, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close (fd);
	return (TRUE);
}

/*
 ** @brief      Check textures specs format.
 **
 ** - each element starts with an ID composed of 2 chars: NO, SO, WE, EA
 ** - followed by all specific info for each object in a strict order
 ** - element's parts are separated with one or more space
 ** - type of element can be separated by empty lines
 **   (type of element ≠ element)
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_check_tex(const char **specs)
{
	int		ids_count;
	int		x;
	int		y;
	int		r;

	ids_count = ft_strlen (TEX_IDS) / TEX_NUM;
	r = TRUE;
	y = 0;
	while (**specs == '\0')
		specs++;
	while (y < TEX_NUM && specs[y][0])
	{
		x = 0;
		r *= (specs[y][x++] == TEX_IDS[y * ids_count]);
		r *= (specs[y][x++] == TEX_IDS[y * ids_count + 1]);
		r *= (specs[y][x++] == ' ');
		while (specs[y][x] == ' ')
			++x;
		r *= ((specs[y][x] != '\0') && ft_check_tex_value (&specs[y][x]));
		y++;
	}
	r *= ((y == TEX_NUM) && (specs[y][0] == '\0'));
	return (r);
}

#include "cube.h"

/*
 ** @brief      Check colors specs value.
 **
 ** - Three numbers, comma-separated:
 **
 **   '<0_to_255>,<0_to_255>,<0_to_255>'
 **   TODO 0003
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_check_col_val(const char *specs)
{
	int		r;
	int		x;
	int		y;
	char	color[3][4];

	r = TRUE;
	y = 0;
	if (!ft_isdigit (*specs))
		return (FALSE);
	while (y < 3)
	{
		x = 0;
		specs += (*specs && *specs == ',');
		while (*specs && *specs != ',' && x < 3)
		{
			r *= ft_isdigit (*specs);
			ft_memcpy ((void *)&color[y][x++], (void *)specs++, 1);
		}
		r *= (!(*specs && ft_isdigit (*specs)));
		color[y][x] = 0;
		r *= (ft_atoi (color[y]) <= 255);
		y++;
	}
	return (r);
}

/*
 ** @brief      Check colors specs format.
 **
 ** - each element starts with an ID composed of 1 char: F, C
 ** - followed by all specific info for each object in a strict order
 ** - element's parts are separated with one or more space
 ** - type of element can be separated by empty lines
 **   (type of element ≠ element)
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_check_col(const char **specs)
{
	int		ids_count;
	int		x;
	int		y;
	t_bool	r;

	ids_count = ft_strlen(COL_IDS) / COL_NUM;
	r = TRUE;
	y = 0;
	while (**specs == '\0')
		specs++;
	while (y < COL_NUM && specs[y][0])
	{
		x = 0;
		r *= (specs[y][x++] == COL_IDS[y * ids_count]);
		r *= (specs[y][x++] == ' ');
		while (specs[y][x] == ' ')
			++x;
		r *= ((specs[y][x] != '\0') && ft_check_col_val(&specs[y][x]));
		y++;
	}
	r *= ((y == COL_NUM) && (specs[y][0] == '\0'));
	return (r);
}

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

static t_bool	ft_check_col_val(const char *specs)
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

static t_bool	ft_check_col_ids(const char **specs)
{
	int	checker[COL_NUM];
	int	i;
	int	j;

	i = -1;
	while (++i < COL_NUM)
		checker[i] = 0;
	i = -1;
	while (++i < COL_NUM)
	{
		if (ft_strchr (COL_IDS, specs[i][0]) == NULL)
			return (FALSE);
		else
			checker[i] = (int) specs[i][0];
		j = i;
		while (j--)
		{
			dprintf (2, "%c == %c\n", checker[i], checker[j]);
			if (checker[i] == checker[j])
				return (FALSE);
		}
	}
	return (TRUE);
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
	int		x;
	int		y;
	t_bool	r;

	r = TRUE;
	y = 0;
	while (**specs == '\0')
		specs++;
	r *= ft_check_col_ids (specs);
	while (y < COL_NUM && specs[y][0])
	{
		x = 0;
		x++;
		r *= (specs[y][x++] == ' ');
		while (specs[y][x] == ' ')
			++x;
		r *= ((specs[y][x] != '\0') && ft_check_col_val(&specs[y][x]));
		y++;
	}
	r *= ((y == COL_NUM) && (specs[y][0] == '\0'));
	return (r);
}

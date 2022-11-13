#include "cube.h"

/*
 ** @brief      Check cub specs format.
 **
 ** - cub specs have at least 11 lines
 **   (4+1 + 2+1 + 3)
 **
 ** Texture specs can    come 1st or 2nd
 ** Colors  specs can    come 1st or 2nd
 ** Map     specs has to come 3rd
 **
 ** @param[in]  specs the cub specificities.
 ** @return     True or false.
 */

static t_bool	ft_check_cub_2(const char **specs)
{
	if (**specs == COL_IDS[0])
	{
		if (ft_check_col (specs) == FALSE)
			return (write (2, "Error\nInvalid .cub colors\n", 27) == 0);
		if (ft_check_tex (specs + COL_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub textures\n", 29) == 0);
		if (ft_check_map (specs + COL_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub map\n", 24) == 0);
	}
	else if (**specs == TEX_IDS[0])
	{
		if (ft_check_tex (specs) == FALSE)
			return (write (2, "Error\nInvalid .cub textures\n", 29) == 0);
		if (ft_check_col (specs + TEX_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub colors\n", 27) == 0);
		if (ft_check_map (specs + TEX_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub map\n", 24) == 0);
	}
	return (TRUE);
}

t_bool	ft_check_cub(const char **specs)
{
	int		height;

	height = 0;
	while (specs[height])
		height++;
	if (height < 11)
		return (FALSE);
	if (**specs != COL_IDS[0] && **specs != TEX_IDS[0])
		return (FALSE);
	if (ft_check_cub_2(specs) == FALSE)
	{
		ft_freetab ((void **)specs);
		return (FALSE);
	}
	return (TRUE);
}

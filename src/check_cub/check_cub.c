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
 */

t_bool	ft_check_cub(const char **specs)
{
	int		height;
	t_bool	r;

	r = TRUE;
	height = 0;
	while (specs[height])
		height++;
	if (height < 11)
		return (FALSE);
	if (**specs == COL_IDS[0])
	{
		r *= ft_check_col (specs);
		r *= ft_check_tex (specs + COL_NUM);
		r *= ft_check_map (specs + COL_NUM);
	}
	else if (**specs == TEX_IDS[0])
	{
		r *= ft_check_tex (specs);
		r *= ft_check_col (specs + TEX_NUM);
		r *= ft_check_map (specs + TEX_NUM);
	}
	else
		return (FALSE);
	return (r);
}

#include "cube.h"

/*
 ** @brief      Extract RGB values from the given spec line
 **
 ** @param[in]  color a spec line corresponding to a color
 ** @return     The RGB values as a string or NULL.
 **
 ** @see ft_init_cub_color
 */

static char	**ft_extract_rgb_val(const char *color)
{
	char	*tmp;
	char	**rgb;

	tmp = ft_strtrim (color, " ");
	if (!tmp)
		return (NULL);
	rgb = ft_split (tmp, ',');
	ft_free (tmp);
	if (!rgb)
		return (NULL);
	return (rgb);
}

/*
 ** @brief      Init cub colors
 **
 ** @param[out] cub the cub structure
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_init_cub_color(t_cub *cub, const char **specs)
{
	char	**rgb;

	while (**specs != 'F')
		specs++;
	rgb = ft_extract_rgb_val (*specs + 1);
	if (!rgb)
		return (FALSE);
	cub->f_color_hex = ft_create_rgb
		(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
	ft_freetab ((void **)rgb);
	specs++;
	rgb = ft_extract_rgb_val (*specs + 1);
	if (!rgb)
		return (FALSE);
	cub->c_color_hex = ft_create_rgb
		(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
	ft_freetab ((void **)rgb);
	return (TRUE);
}

/*
 ** @brief      Init the cub map
 **
 ** @param[out] cub the cub structure
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_init_cub_texture(t_cub *cub, const char **specs)
{
	char	*texture;
	int		i;

	while (**specs != 'N')
		specs++;
	i = 0;
	while (i < 4)
	{
		texture = ft_strtrim (&specs[i][2], " ");
		if (!texture)
			return (FALSE);
		if (i == 0)
			cub->n_texture = texture;
		if (i == 1)
			cub->s_texture = texture;
		if (i == 2)
			cub->w_texture = texture;
		if (i == 3)
			cub->e_texture = texture;
		i++;
	}
	return (TRUE);
}


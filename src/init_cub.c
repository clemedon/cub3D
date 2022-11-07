#include "cube.h"

static t_bool	ft_init_cub_color(t_cub *cub, const char **specs)
{
	char	**rgb;

	while (**specs != 'F')
		specs++;
	rgb = ft_split (ft_strtrim (*specs + 1, " "), ',');
	if (!rgb)
		return (FALSE);
	cub->f_color_hex = ft_create_rgb
		(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
	ft_freetab ((void **)rgb);
	specs++;
	rgb = ft_split (ft_strtrim (*specs + 1, " "), ',');
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
 ** @param[i/o] cub the cub structure
 ** @param[in]  specs the cub specs
 */

static t_bool	ft_init_cub_texture(t_cub *cub, const char **specs)
{
	char	*texture;
	int		i;

	while (**specs != 'N')
		specs++;
	i = 0;
	while (i < 4)
	{
		texture = ft_strdup (ft_strtrim (&specs[i][2], " "));
		if (!texture)
			return (FALSE);
		if (i == 0)
			cub->n_texture_fd = texture;
		if (i == 1)
			cub->s_texture_fd = texture;
		if (i == 2)
			cub->w_texture_fd = texture;
		if (i == 3)
			cub->e_texture_fd = texture;
		i++;
	}
	return (TRUE);
}

/*
 ** @brief      Convert row of chars to row of int
 **
 ** Convert each character of a string into its corresponding numerical ID.
 **
 ** @param[in]  str an array of chars
 ** @return     The numerical id corresponding to the given char.
 **
 ** TODO init utils .c ?
 */

static int	*ft_maprow_to_int(const char *maprow, int *introw, int width)
{
	int	i;

	ft_memset ((void *)introw, -1, width * sizeof (int));
	i = 0;
	while (maprow[i])
	{
		if (maprow[i] == ' ')
			introw[i] = -1;
		else if (maprow[i] == '0')
			introw[i] = 0;
		else if (maprow[i] == '1')
			introw[i] = 1;
		else if (maprow[i] == 'N')
			introw[i] = 2;
		else if (maprow[i] == 'S')
			introw[i] = 3;
		else if (maprow[i] == 'E')
			introw[i] = 4;
		else if (maprow[i] == 'W')
			introw[i] = 5;
		i++;
	}
	return (introw);
}

/*
 ** @brief      Convert map of chars to map of int
 **
 ** @param[in]  charmap our map
 ** @param[in]  width the map width
 ** @param[in]  height the map height
 ** @return     An integer version of the map
 **
 ** TODO init utils .c ?
 */

static int	**ft_map_to_int(const char **charmap, int width, int height)
{
	int	**intmap;
	int	*introw;
	int	y;

	intmap = malloc (sizeof (int *) * (height + 1));
	if (!intmap)
		return (NULL);
	y = 0;
	while (y < height)
	{
		introw = malloc (sizeof (int) * (width + 1));
		if (!introw)
		{
			intmap[y] = 0;
			ft_freetab ((void **)intmap);
			return (NULL);
		}
		intmap[y] = ft_maprow_to_int(charmap[y], introw, width);
		y++;
	}
	return (intmap);
}

/*
 ** @brief      Init the cub map
 **
 ** @param[i/o] cub the cub structure
 ** @param[in]  specs the cub specs
 **
 ** TODO init_map
 ** starting with an emptyline is not legal?
 */

static t_bool	ft_init_cub_map(t_cub *cub, const char **specs)
{
	while (ft_strchr(MAP_OUTER, **specs) == NULL || **specs == 0)
		specs++;
	cub->height = ft_strtab_height (specs);
	cub->width = ft_strtab_width (specs);
	cub->map = ft_map_to_int (specs, cub->width, cub->height);
	if (cub->map == NULL)
		return (FALSE);
	ft_print_readable_map(cub->map, cub->width, cub->height);
	return (TRUE);
}

/*
 ** @brief      Init cub struct
 **
 ** @param[out] cub the struct
 ** @param[in]  specs the data to fill cub with
 */

void	ft_init_cub(t_cub *cub, const char **specs)
{
	cub->specs = specs;
	if (!ft_check_cub (specs))
	{
		ft_freetab ((void **)specs);
		ft_exit_error (__func__, ER_SPECS);
	}
	ft_init_cub_color (cub, specs);
	ft_init_cub_texture (cub, specs);
	if (!ft_init_cub_map (cub, specs))
	{
		ft_freetab ((void **)specs);
		ft_exit_error (__func__, ER_SPECS);
	}
}

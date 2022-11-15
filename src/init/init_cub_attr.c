/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:18:29 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 14:45:23 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_bool	ft_init_cub_color_fc(t_cub *cub, const char **specs)
{
	char	**rgb;

	specs++;
	if (**specs == 'F')
	{
		rgb = ft_extract_rgb_val (*specs + 1);
		if (!rgb)
			return (FALSE);
		cub->f_color_hex = ft_create_rgb
			(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
		ft_freetab ((void **)rgb);
	}
	else if (**specs == 'C')
	{
		rgb = ft_extract_rgb_val (*specs + 1);
		if (!rgb)
			return (FALSE);
		cub->c_color_hex = ft_create_rgb
			(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
		ft_freetab ((void **)rgb);
	}
	return (TRUE);
}

static t_bool	ft_init_cub_color_cf(t_cub *cub, const char **specs)
{
	char	**rgb;

	if (**specs == 'C')
	{
		rgb = ft_extract_rgb_val (*specs + 1);
		if (!rgb)
			return (FALSE);
		cub->c_color_hex = ft_create_rgb
			(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
		ft_freetab ((void **)rgb);
	}
	else if (**specs == 'F')
	{
		rgb = ft_extract_rgb_val (*specs + 1);
		if (!rgb)
			return (FALSE);
		cub->f_color_hex = ft_create_rgb
			(ft_atoi (rgb[0]), ft_atoi (rgb[1]), ft_atoi (rgb[2]));
		ft_freetab ((void **)rgb);
	}
	return (TRUE);
}

t_bool	ft_init_cub_color(t_cub *cub, const char **specs)
{
	specs += 4 * (ft_strchr (TEX_IDS, **specs) != NULL);
	while (**specs == '\0')
		specs++;
	if (!ft_init_cub_color_cf (cub, specs))
		return (FALSE);
	if (!ft_init_cub_color_fc (cub, specs))
		return (FALSE);
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

	specs += 2 * (ft_strchr (COL_IDS, **specs) != NULL);
	while (**specs == '\0')
		specs++;
	i = 0;
	while (i < 4)
	{
		texture = ft_strtrim (&specs[i][2], " ");
		if (!texture)
			return (FALSE);
		if (specs[i][0] == 'N')
			cub->n_texture = texture;
		if (specs[i][0] == 'S')
			cub->s_texture = texture;
		if (specs[i][0] == 'W')
			cub->w_texture = texture;
		if (specs[i][0] == 'E')
			cub->e_texture = texture;
		i++;
	}
	return (TRUE);
}

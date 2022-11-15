/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:08:59 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 14:31:56 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_bool	ft_check_cub_elements(const char **specs)
{
	if (**specs == '\0')
		return (write (2, "Error\nInvalid .cub file first line\n", 35) == 0);
	if (ft_strchr (COL_IDS, **specs) != NULL)
	{
		if (ft_check_col (specs) == FALSE)
			return (write (2, "Error\nInvalid .cub colors\n", 26) == 0);
		if (ft_check_tex (specs + COL_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub textures\n", 28) == 0);
		if (ft_check_map (specs + COL_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub map\n", 23) == 0);
	}
	else if (ft_strchr (TEX_IDS, **specs) != NULL)
	{
		if (ft_check_tex (specs) == FALSE)
			return (write (2, "Error\nInvalid .cub textures\n", 28) == 0);
		if (ft_check_col (specs + TEX_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub colors\n", 26) == 0);
		if (ft_check_map (specs + TEX_NUM) == FALSE)
			return (write (2, "Error\nInvalid .cub map\n", 23) == 0);
	}
	else
		return (write (2, "Error\nInvalid .cub first line\n", 30) == 0);
	return (TRUE);
}

t_bool	ft_check_cub(const char **specs)
{
	int		height;

	height = 0;
	while (specs[height + 1])
		height++;
	if (*specs[height] == '\0')
	{
		ft_freetab ((void **)specs);
		return (write (2, "Error\nInvalid .cub map\n", 23) == 0);
	}
	if (ft_check_cub_elements(specs) == FALSE)
	{
		ft_freetab ((void **)specs);
		return (FALSE);
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:17:35 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:17:53 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      Convert row of chars to row of int
 **
 ** Convert each character of a string into its corresponding numerical ID.
 **
 ** @param[in]  str an array of chars
 ** @return     The numerical id corresponding to the given char.
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
		intmap[y] = ft_maprow_to_int (charmap[y], introw, width);
		y++;
	}
	return (intmap);
}

/*
 ** @brief      Init the cub map
 **
 ** @param[out] cub the cub structure
 ** @param[in]  specs the cub specs
 */

t_bool	ft_init_cub_map(t_cub *cub, const char **specs)
{
	while (ft_strchr(MAP_OUTER, **specs) == NULL || **specs == 0)
		specs++;
	cub->height = ft_strtab_height (specs);
	cub->width = ft_strtab_width (specs);
	cub->map = ft_map_to_int (specs, cub->width, cub->height);
	if (cub->map == NULL)
		return (FALSE);
	return (TRUE);
}

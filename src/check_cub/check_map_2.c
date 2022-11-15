/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:13:57 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:14:00 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      Check if the map is surrounded by walls
 **
 ** - Check that every "NSEW0" are only in contact with a "NSEW01".
 **
 ** @param[in]  map the cub map
 ** @return     True of false
 */

static t_bool	ft_check_map_enclosure_2(char **map, int x, int y)
{
	t_bool	check;

	check = 0;
	if (map[y][x] == *MAP_ROOM || ft_strchr (MAP_SPAWN, map[y][x]))
	{
		if (!map[y][x - 1] || !map[y][x + 1])
			return (FALSE);
		if (!map[y - 1][x] || !map[y + 1][x])
			return (FALSE);
		if (map[y][x - 1])
			check += (ft_strchr (MAP_INNER, map[y][x - 1]) != NULL);
		if (map[y][x + 1])
			check += (ft_strchr (MAP_INNER, map[y][x + 1]) != NULL);
		if (map[y - 1][x])
			check += (ft_strchr (MAP_INNER, map[y - 1][x]) != NULL);
		if (map[y + 1][x])
			check += (ft_strchr (MAP_INNER, map[y + 1][x]) != NULL);
		if (check != 4)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ft_check_map_enclosure(char **map, int width, int height)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < height)
	{
		while (x < width)
		{
			if (!ft_check_map_enclosure_2 (map, x, y))
				return (FALSE);
			x++;
		}
		x = 0;
		y++;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:11:20 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 14:45:06 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      Check map enclosure
 **
 ** - the player area should be enclosed with walls
 **
 ** @param[in]  map the cub map
 ** @return     True or false.
 */

static t_bool	ft_check_map_limits(const char **map)
{
	int		width;
	int		height;
	char	**grid;

	height = ft_strtab_height (map);
	width = ft_strtab_width (map);
	grid = ft_gridify (map, width, height);
	if (!grid)
		return (FALSE);
	if (!ft_check_map_enclosure (grid, width, height))
	{
		ft_freetab ((void **)grid);
		return (FALSE);
	}
	ft_freetab ((void **)grid);
	return (TRUE);
}

/*
 ** @brief      Check if there is only one spawning point
 **
 ** - only one spawn point allowed
 **
 ** @param[in]  map the cub map
 ** @return     True or false
 */

static t_bool	ft_check_map_spawn(const char **map)
{
	int	spawn_number;

	spawn_number = 0;
	while (*map)
	{
		if (ft_strcharset (MAP_SPAWN, *map))
			spawn_number++;
		map++;
	}
	return (spawn_number == 1);
}

/*
 ** @brief      Check global map specs format.
 **
 ** - map first line contains only " 1"
 ** - map first line contains at least a "1"
 **
 ** - map inner lines contain of only "NSEW 01"
 ** - map inner lines contain at least a "NSEW 01"
 **
 ** - map last line contains only " 1"
 ** - map last line contains at least "1"
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false
 */

static t_bool	ft_check_map_global(const char **map)
{
	int		y;
	t_bool	r;

	r = TRUE;
	y = 0;
	r *= ft_str_onlywith (map[y], MAP_OUTER);
	r *= (ft_strchr (map[y], *MAP_WALL) != NULL);
	while (map[++y])
	{
		r *= ft_str_onlywith (map[y], MAP_VALID);
		r *= (ft_strchr (map[y], *MAP_WALL) != NULL);
	}
	return (r);
	r *= ft_str_onlywith (map[y], MAP_OUTER);
	r *= (ft_strchr (map[y], *MAP_WALL) != NULL);
	return (r);
}

/*
 ** @brief      Check map specs format
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false
 */

t_bool	ft_check_map(const char **specs)
{
	while (**specs == '\0')
		specs++;
	if (ft_strchr (COL_IDS, **specs) != NULL)
		specs += 2;
	else if (ft_strchr (TEX_IDS, **specs) != NULL)
		specs += 4;
	while (**specs == '\0')
		specs++;
	if (ft_strchr (COL_IDS, **specs) != NULL)
		specs += 2;
	else if (ft_strchr (TEX_IDS, **specs) != NULL)
		specs += 4;
	while (**specs == '\0')
		specs++;
	if (!ft_check_map_global (specs))
		return (FALSE);
	if (!ft_check_map_spawn (specs))
		return (FALSE);
	if (!ft_check_map_limits (specs))
		return (FALSE);
	return (TRUE);
}

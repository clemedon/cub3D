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

static t_bool	ft_check_map_enclosure(char **map, int width, int height)
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

t_bool	ft_check_map_global(const char **map)
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
	specs += 2 * (ft_strchr (COL_IDS, **specs) != NULL);
	specs += 4 * (ft_strchr (TEX_IDS, **specs) != NULL);
	while (**specs == '\0')
		specs++;
	specs += 2 * (ft_strchr (COL_IDS, **specs) != NULL);
	specs += 4 * (ft_strchr (TEX_IDS, **specs) != NULL);
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

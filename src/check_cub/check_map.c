#include "cube.h"

/*
 ** @brief      Check if the map is surrounded by walls
 **
 ** - Check that every "NSEW0" are only in contact with a "NSEW01".
 **
 ** @param[in]  grid the cub specs map grid
 ** @return     True of false
 */

t_bool	ft_check_map_enclosure(char **grid, int width, int height)
{
	int		x;
	int		y;
	t_bool	check;

	x = 0;
	y = 0;
	check = 0;
	while (y < height)
	{
		while (x < width)
		{
			if (grid[y][x] == *MAP_ROOM || ft_strchr (MAP_SPAWN, grid[y][x]))
			{
				if (!grid[y][x - 1] || !grid[y][x + 1])
					return (ft_return_msg (__func__, FALSE));
				if (!grid[y - 1][x] || !grid[y + 1][x])
					return (ft_return_msg (__func__, FALSE));
				if (grid[y][x - 1])
					check += (ft_strchr (MAP_INNER, grid[y][x - 1]) != NULL);
				if (grid[y][x + 1])
					check += (ft_strchr (MAP_INNER, grid[y][x + 1]) != NULL);
				if (grid[y - 1][x])
					check += (ft_strchr (MAP_INNER, grid[y - 1][x]) != NULL);
				if (grid[y + 1][x])
					check += (ft_strchr (MAP_INNER, grid[y + 1][x]) != NULL);
				if (check != 4)
					return (ft_return_msg (__func__, FALSE));
				check = 0;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (TRUE);
}

/*
 ** @brief      Create a grid from the map
 **
 ** Unlike the map, the grid's rows have all the same width that correspond
 ** to the longest map row width.
 **
 ** @param[in]  map the cub specs map
 ** @return     A pointer to the grid
 */

char	**ft_mapgrid(const char **map, int width, int height)
{
	int		y;
	char	**grid;

	grid = malloc (sizeof (char *) * (height + 1));
	if (!grid)
		return (NULL);
	y = 0;
	while (y < height)
	{
		grid[y] = malloc (sizeof (char) * (width + 1));
		if (!grid[y])
		{
			grid[y] = 0;
			ft_freetab ((void **)grid);
			return (NULL);
		}
		ft_memset ((void *)grid[y], ' ', width);
		ft_memcpy ((void *)grid[y], (void *)map[y], ft_strlen (map[y]));
		grid[y][width] = 0;
		y++;
	}
	grid[y] = 0;
	ft_print_chartab ((const char **) grid);
	return (grid);
}

/*
 ** @brief      Check map enclosure
 **
 ** - the player area should be enclosed with walls
 **
 ** @param[in]  map the cub map
 ** @return     True or false.
 */

t_bool	ft_check_map_limits(const char **map)
{
	int		width;
	int		height;
	char	**grid;

	height = ft_strtab_height (map);
	width = ft_strtab_width (map);
	grid = ft_mapgrid (map, width, height);
	if (!grid)
		return (ft_return_msg (__func__, FALSE));
	if (!ft_check_map_enclosure (grid, width, height))
	{
		ft_freetab ((void **)grid);
		return (ft_return_msg (__func__, FALSE));
	}
	ft_freetab ((void **)grid);
	return (TRUE);
}

/*
 ** @brief      Check if there is only one spawning point
 **
 ** - only one spawn point allowed
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false
 */

t_bool	ft_check_map_spawn(const char **map)
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
	while (**specs == '\0')
		specs++;
	specs += (COL_NUM * (**specs == COL_IDS[0]));
	specs += (TEX_NUM * (**specs == TEX_IDS[0]));
	while (**specs == '\0')
		specs++;
	if (!ft_check_map_global (specs))
		return (ft_return_msg (__func__, FALSE));
	if (!ft_check_map_spawn (specs))
		return (ft_return_msg (__func__, FALSE));
	if (!ft_check_map_limits (specs))
		return (ft_return_msg (__func__, FALSE));
	return (TRUE);
}

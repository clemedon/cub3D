/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:34:01 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:39:37 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      Turn 2D array into grid
 **
 ** "A rectangular array of elements of equal length."
 **
 ** The grid width should correspond to its longest row width.
 **
 ** @param[in]  map the cub specs map
 ** @return     A pointer to the grid
 */

char	**ft_gridify(const char **tab, int width, int height)
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
			ft_freetab ((void **)tab);
			return (NULL);
		}
		ft_memset ((void *)grid[y], ' ', width);
		ft_memcpy ((void *)grid[y], (void *)tab[y], ft_strlen (tab[y]));
		grid[y][width] = 0;
		y++;
	}
	grid[y] = 0;
	return (grid);
}

/*
 ** @brief      Open a file.
 **
 ** @param[in]  file a file.
 ** return      A file descriptor.
 */

int	ft_open(const char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
		ft_exit_error (__func__, strerror (errno));
	return (fd);
}

/*
 ** @brief      Create rgb value
 **
 ** @param[in]  r the red value
 ** @param[in]  g the green value
 ** @param[in]  b the blue value
 ** @return     An rgb number
 */

unsigned long	ft_create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*
 ** @brief      Print an error message and exit.
 **
 ** @param[in]  func the function causing the error.
 ** @param[in]  strerror the message to print.
 **
 ** TODO rename ft_exit_errmsg
 */

void	ft_exit_error(const char *func, const char *strerror)
{
	if (!strerror)
	{
		ft_putstr_fd ((char *)(unsigned long)func, 2);
		ft_putendl_fd (": undefined error", 2);
	}
	else if (!func)
	{
		ft_putendl_fd ((char *)(unsigned long)strerror, 2);
	}
	else
	{
		ft_putstr_fd ((char *)(unsigned long)func, 2);
		ft_putstr_fd (": ", 2);
		ft_putendl_fd ((char *)(unsigned long)strerror, 2);
	}
	exit (errno);
}

void	ft_quit(t_data *data)
{
	ft_free_cub (&data->cub);
	ft_free_texture (&data->cub, &data->mlx);
	ft_free_minimap (&data->minimap);
	ft_free_mlx (&data->mlx);
	exit(EXIT_SUCCESS);
}

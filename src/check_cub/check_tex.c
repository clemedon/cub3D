/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:11:44 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:11:45 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      Check texture specs value.
 **
 ** - has to be a valid readable file
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

static t_bool	ft_check_tex_value(const char *specs)
{
	int	fd;

	fd = open (specs, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close (fd);
	fd = open (specs, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	ft_check_tex_ids(const char **specs)
{
	int	checker[TEX_NUM];
	int	i;
	int	j;

	i = -1;
	while (++i < TEX_NUM)
		checker[i] = 0;
	i = -1;
	while (++i < TEX_NUM)
	{
		if (ft_strchr (TEX_IDS, specs[i][0]) == NULL)
			return (FALSE);
		else
			checker[i] = (int) specs[i][0];
		j = i;
		while (j--)
			if (checker[i] == checker[j])
				return (FALSE);
	}
	return (TRUE);
}

/*
 ** @brief      Check textures specs format.
 **
 ** - each element starts with an ID composed of 2 chars: NO, SO, WE, EA
 ** - followed by all specific info for each object in a strict order
 ** - element's parts are separated with one or more space
 ** - type of element can be separated by empty lines
 **   (type of element ≠ element)
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_check_tex(const char **specs)
{
	int		x;
	int		y;
	int		r;

	r = TRUE;
	y = 0;
	while (**specs == '\0')
		specs++;
	r *= ft_check_tex_ids (specs);
	while (y < TEX_NUM && specs[y][0])
	{
		x = 0;
		x += ft_strlen (TEX_IDS) / TEX_NUM;
		r *= (specs[y][x++] == ' ');
		while (specs[y][x] == ' ')
			++x;
		r *= ((specs[y][x] != '\0') && ft_check_tex_value (&specs[y][x]));
		y++;
	}
	r *= ((y == TEX_NUM) && specs[y] && (specs[y][0] == '\0'));
	return (r);
}

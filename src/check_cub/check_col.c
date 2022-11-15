/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:32:31 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 11:32:31 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      Check colors specs value.
 **
 ** - 3 numbers made of 1 to 3 digits, comma-separated:
 **
 **   '<0_to_255>,<0_to_255>,<0_to_255>'
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

static t_bool	ft_check_col_value(const char *specs)
{
	int		x;
	int		y;
	char	col[3][4];

	y = 0;
	while (y < 3)
	{
		x = 0;
		if (*specs && specs[0] == '0' && ft_isdigit(specs[1]))
			return (FALSE);
		while (*specs && *specs != ',')
		{
			if (!ft_isdigit (*specs) || (x >= 3))
				return (FALSE);
			ft_memcpy ((void *)&col[y][x++], (void *)specs++, 1);
		}
		if (y == 2 && (*specs != '\0'))
			return (FALSE);
		col[y][x] = '\0';
		if ((col[y][0] == 0) || (ft_atoi (col[y]) > 255 || ft_atoi(col[y]) < 0))
			return (FALSE);
		y++;
		specs += (*specs && *specs == ',');
	}
	return (TRUE);
}

static t_bool	ft_check_col_ids(const char **specs)
{
	int	checker[COL_NUM];
	int	i;
	int	j;

	i = -1;
	while (++i < COL_NUM)
		checker[i] = 0;
	i = -1;
	while (++i < COL_NUM)
	{
		if (ft_strchr (COL_IDS, specs[i][0]) == NULL)
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
 ** @brief      Check colors specs format.
 **
 ** - each element starts with an ID composed of 1 char: F, C
 ** - followed by all specific info for each object in a strict order
 ** - element's parts are separated with one or more space
 ** - type of element can be separated by empty lines
 **   (type of element ≠ element)
 **
 ** @param[in]  specs the cub specs
 ** @return     True or false.
 */

t_bool	ft_check_col(const char **specs)
{
	int		x;
	int		y;
	t_bool	r;

	r = TRUE;
	y = 0;
	while (**specs == '\0')
		specs++;
	r *= ft_check_col_ids (specs);
	while (y < COL_NUM && specs[y][0])
	{
		x = 0;
		x += ft_strlen (COL_IDS) / COL_NUM;
		r *= (specs[y][x++] == ' ');
		while (specs[y][x] == ' ')
			++x;
		r *= ((specs[y][x] != '\0') && ft_check_col_value (&specs[y][x]));
		y++;
	}
	r *= ((y == COL_NUM) && (specs[y][0] == '\0'));
	return (r);
}

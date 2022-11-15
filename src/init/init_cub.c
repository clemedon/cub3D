/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:16:19 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:17:15 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_cub(t_cub *cub)
{
	ft_free (cub->n_texture);
	ft_free (cub->s_texture);
	ft_free (cub->w_texture);
	ft_free (cub->e_texture);
	if (cub->specs)
		ft_freetab ((void **)cub->specs);
	if (cub->map)
		ft_freetab_size ((void **)cub->map, cub->height);
}

static void	ft_pre_init_cub(t_cub *cub)
{
	cub->minimap = -1;
	cub->ray = -1;
	cub->specs = NULL;
	cub->width = 0;
	cub->height = 0;
	cub->map = NULL;
	cub->f_color_hex = 0;
	cub->c_color_hex = 0;
	cub->n_texture = NULL;
	cub->s_texture = NULL;
	cub->w_texture = NULL;
	cub->e_texture = NULL;
}

/*
 ** @brief      Init cub struct
 **
 ** @param[out] cub the struct
 ** @param[in]  specs the data to fill cub with
 */

t_bool	ft_init_cub(t_cub *cub, const char **specs)
{
	ft_pre_init_cub(cub);
	cub->specs = specs;
	if (!ft_init_cub_color (cub, specs))
		return (FALSE);
	if (!ft_init_cub_texture (cub, specs))
		return (FALSE);
	if (!ft_init_cub_map (cub, specs))
		return (FALSE);
	return (TRUE);
}

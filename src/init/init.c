/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:15:51 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:16:05 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_bool	ft_init(t_data *data, const char **specs)
{
	if (!ft_init_cub (&data->cub, specs))
	{
		ft_free_cub (&data->cub);
		return (FALSE);
	}
	if (!ft_init_mlx(&data->mlx))
	{
		ft_free_cub (&data->cub);
		ft_free_mlx (&data->mlx);
		return (FALSE);
	}
	if (!ft_init_texture(&data->cub, &data->mlx))
	{
		ft_free_texture (&data->cub, &data->mlx);
		ft_free_cub (&data->cub);
		ft_free_mlx (&data->mlx);
		return (FALSE);
	}
	ft_pre_init_minimap(data);
	ft_init_player(data);
	ft_init_rays(data);
	return (TRUE);
}

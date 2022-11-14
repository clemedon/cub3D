/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:00:32 by athirion          #+#    #+#             */
/*   Updated: 2022/11/14 17:01:48 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_minimap(t_minimap *minimap)
{
	if (minimap->mlx.img_ptr)
		mlx_destroy_image(minimap->mlx.mlx_ptr, minimap->mlx.img_ptr);
	if (minimap->mlx.win_ptr)
		mlx_destroy_window(minimap->mlx.mlx_ptr, minimap->mlx.win_ptr);
	if (minimap->mlx.mlx_ptr)
		mlx_destroy_display(minimap->mlx.mlx_ptr);
	free(minimap->mlx.mlx_ptr);
}

void	ft_pre_init_minimap(t_data *data)
{
	data->minimap.mlx.img_ptr = NULL;
	data->minimap.mlx.win_ptr = NULL;
	data->minimap.mlx.mlx_ptr = NULL;
	data->minimap.mlx.addr = NULL;
	data->minimap.mlx.bpp = 0;
	data->minimap.mlx.endian = 0;
	data->minimap.mlx.line_length = 0;
	data->minimap.rays = -1;
}

static int	ft_init_minimap(t_data *data, t_minimap *minimap)
{
	if (!minimap->mlx.mlx_ptr)
	{
		ft_pre_init_minimap(data);
		minimap->mlx.mlx_ptr = mlx_init();
		if (!minimap->mlx.mlx_ptr)
			return (FALSE);
		minimap->mlx.win_ptr = mlx_new_window(minimap->mlx.mlx_ptr,
				data->cub.width * MINIMAP_SIZE * MAP_SCALE,
				data->cub.height * MINIMAP_SIZE * MAP_SCALE, "minimap");
		if (!minimap->mlx.win_ptr)
			return (FALSE);
	}
	return (TRUE);
}

static int	ft_render_minimap(t_data *data, t_minimap *minimap)
{
	if (minimap->mlx.img_ptr)
		mlx_destroy_image(minimap->mlx.mlx_ptr, minimap->mlx.img_ptr);
	minimap->mlx.img_ptr = mlx_new_image(minimap->mlx.mlx_ptr,
			data->cub.width * MINIMAP_SIZE * MAP_SCALE,
			data->cub.height * MINIMAP_SIZE * MAP_SCALE);
	if (!minimap->mlx.img_ptr)
		return (FALSE);
	minimap->mlx.addr = mlx_get_data_addr(minimap->mlx.img_ptr,
			&minimap->mlx.bpp,
			&minimap->mlx.line_length,
			&minimap->mlx.endian);
	if (!minimap->mlx.addr)
		return (FALSE);
	ft_draw_mini_map(data, minimap);
	ft_draw_player(data, minimap);
	if (data->cub.ray == 1)
		ft_draw_rays(data, minimap);
	mlx_put_image_to_window(minimap->mlx.mlx_ptr, minimap->mlx.win_ptr,
		minimap->mlx.img_ptr, 0, 0);
	return (TRUE);
}

void	ft_minimap(t_data *data)
{
	if (data->cub.minimap == 1)
	{
		if (!ft_init_minimap(data, &data->minimap))
		{
			ft_free_minimap(&data->minimap);
			ft_quit(data);
		}
		if (!ft_render_minimap(data, &data->minimap))
		{
			ft_free_minimap(&data->minimap);
			ft_quit(data);
		}
	}
}

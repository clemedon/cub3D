/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:21:44 by athirion          #+#    #+#             */
/*   Updated: 2022/11/15 14:53:46 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_draw_mini_map(t_data *data, t_minimap *minimap)
{
	t_point	p;
	int		i;
	int		j;

	p.x = 0;
	p.y = 0;
	p.color = data->cub.f_color_hex;
	i = -1;
	ft_draw_rect(&minimap->mlx, p, MINIMAP_SIZE * data->cub.width * MAP_SCALE,
		MINIMAP_SIZE * data->cub.height * MAP_SCALE);
	p.color = data->cub.c_color_hex;
	while (++i < data->cub.height)
	{
		j = -1;
		p.x = 0;
		while (++j < data->cub.width)
		{
			if (data->cub.map[i][j] == 1)
				ft_draw_rect(&minimap->mlx, p, MINIMAP_SIZE * MAP_SCALE,
					MINIMAP_SIZE * MAP_SCALE);
			p.x += MINIMAP_SIZE * MAP_SCALE;
		}
		p.y += MINIMAP_SIZE * MAP_SCALE;
	}
}

void	ft_draw_player(t_data *data, t_minimap *minimap)
{
	t_point	p;

	p.x = round (data->player.x * MAP_SCALE / 2);
	p.y = round (data->player.y * MAP_SCALE / 2);
	p.color = data->cub.c_color_hex;
	ft_draw_circle(&minimap->mlx, p, 2);
}

void	ft_draw_rays(t_data *data, t_minimap *minimap)
{
	int		i;
	t_point	p_start;
	t_point	p_end;

	(void) minimap;
	i = 0;
	p_start.x = data->player.x * MAP_SCALE / 2;
	p_start.y = data->player.y * MAP_SCALE / 2;
	p_start.color = data->cub.c_color_hex;
	p_end.color = p_start.color;
	while (i < NUM_RAYS)
	{
		p_end.x = round(data->rays[i].wall_hit_x * MAP_SCALE / 2);
		p_end.y = round(data->rays[i].wall_hit_y * MAP_SCALE / 2);
		ft_draw_line(&data->minimap.mlx, p_start, p_end);
		i += 80;
	}
}

int	ft_render(t_data *data)
{
	if (data->mlx.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->mlx.img_ptr)
		return (FALSE);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img_ptr,
			&data->mlx.bpp, &data->mlx.line_length, &data->mlx.endian);
	if (!data->mlx.addr)
		return (FALSE);
	ft_cast_all_rays(data);
	ft_3d_projection(data);
	ft_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.img_ptr, 0, 0);
	return (TRUE);
}

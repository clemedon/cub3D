/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:18:53 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 15:19:55 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_get_player_position(t_data *data)
{
	float	i;
	float	j;

	i = 0;
	while (i < data->cub.height)
	{
		j = 0;
		while (j < data->cub.width)
		{
			if (data->cub.map[(int) i][(int) j] > 1)
			{
				data->player.x = (float) j * TILE_SIZE + TILE_SIZE / 2;
				data->player.y = (float) i * TILE_SIZE + TILE_SIZE / 2;
				data->player.d_start = data->cub.map[(int) i][(int) j];
				return ;
			}
			j ++;
		}
		i ++;
	}
}

static void	ft_get_player_orientation(t_data *data)
{
	if (data->player.d_start == N)
		data->player.rotation_angle = PI * 1.5;
	else if (data->player.d_start == S)
		data->player.rotation_angle = PI * 0.5;
	else if (data->player.d_start == E)
		data->player.rotation_angle = 0;
	else if (data->player.d_start == W)
		data->player.rotation_angle = PI;
}

void	ft_init_player(t_data *data)
{
	ft_get_player_position(data);
	data->player.dx = 0;
	data->player.dy = 0;
	ft_get_player_orientation(data);
	data->player.width = 1;
	data->player.height = 1;
	data->player.walk_direction = 0;
	data->player.side_direction = 0;
	data->player.turn_direction = 0;
	data->player.walk_speed = WALK_SPEED;
	data->player.turn_speed = TURN_SPEED;
}

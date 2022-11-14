/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:22:13 by athirion          #+#    #+#             */
/*   Updated: 2022/11/14 16:56:55 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_key_event(int key, t_data *data)
{
	if (key == ESCAPE)
		ft_quit(data);
	else if (key == MOVE_FRONT)
		data->player.walk_direction = 1;
	else if (key == MOVE_BACK)
		data->player.walk_direction = -1;
	else if (key == MOVE_RIGHT)
		data->player.side_direction = 1;
	else if (key == MOVE_LEFT)
		data->player.side_direction = -1;
	else if (key == TURN_LEFT)
		data->player.turn_direction = -1;
	else if (key == TURN_RIGHT)
		data->player.turn_direction = 1;
	else if (key == MINIMAP)
	{
		if (data->cub.minimap == 1)
		{
			ft_free_minimap(&data->minimap);
			ft_pre_init_minimap(data);
		}
		data->cub.minimap *= -1;
	}
	else if (key == RAY)
		data->cub.ray *= -1;
}

void	ft_key_release(int key, t_data *data)
{
	if (key == MOVE_FRONT)
		data->player.walk_direction = 0;
	else if (key == MOVE_BACK)
		data->player.walk_direction = 0;
	else if (key == MOVE_RIGHT)
		data->player.side_direction = 0;
	else if (key == MOVE_LEFT)
		data->player.side_direction = 0;
	else if (key == TURN_LEFT)
		data->player.turn_direction = 0;
	else if (key == TURN_RIGHT)
		data->player.turn_direction = 0;
}

void	ft_mouse_event(t_data *data)
{
	ft_quit(data);
}

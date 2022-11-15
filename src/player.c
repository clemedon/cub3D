/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:20:38 by athirion          #+#    #+#             */
/*   Updated: 2022/11/15 12:21:58 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_side_move(t_data *data, t_point *p)
{
	float	step;

	step = data->player.side_direction * data->player.walk_speed;
	p->x = data->player.x + step * sin(data->player.rotation_angle);
	p->y = data->player.y - step * cos(data->player.rotation_angle);
}

static void	ft_oblique_move(t_data *data, t_point *p)
{
	float	step;

	step = data->player.walk_direction * data->player.walk_speed;
	if (data->player.side_direction == 1)
	{
		p->x = data->player.x + step
			* cos(data->player.rotation_angle - PI / 4);
		p->y = data->player.y + step
			* sin(data->player.rotation_angle - PI / 4);
	}
	else if (data->player.side_direction == -1)
	{
		p->x = data->player.x + step
			* cos(data->player.rotation_angle + PI / 4);
		p->y = data->player.y + step
			* sin(data->player.rotation_angle + PI / 4);
	}
}

static void	ft_straight_move(t_data *data, t_point *p)
{
	float	step;

	step = data->player.walk_direction * data->player.walk_speed;
	p->x = data->player.x + cos(data->player.rotation_angle) * step;
	p->y = data->player.y + sin(data->player.rotation_angle) * step;
}

int	ft_move_player(t_data *data)
{
	t_point	p;

	p.x = data->player.x;
	p.y = data->player.y;
	data->player.rotation_angle
		+= data->player.turn_direction * data->player.turn_speed;
	if (data->player.walk_direction == 1 && data->player.side_direction)
		ft_oblique_move(data, &p);
	else if (!data->player.walk_direction && data->player.side_direction)
		ft_side_move(data, &p);
	else
		ft_straight_move(data, &p);
	if (!ft_is_wall(data, p.x, p.y))
	{
		data->player.x = p.x;
		data->player.y = p.y;
	}
	if (!ft_render(data))
		ft_quit (data);
	return (TRUE);
}

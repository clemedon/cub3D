/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:14:59 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 11:15:01 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_init_rays(t_data *data)
{
	int	ray_id;

	ray_id = 0;
	while (ray_id < NUM_RAYS)
	{
		data->rays[ray_id].ray_facing_down = 0;
		data->rays[ray_id].ray_facing_up = 0;
		data->rays[ray_id].ray_facing_left = 0;
		data->rays[ray_id].ray_facing_right = 0;
		data->rays[ray_id].wall_hit_x = 0;
		data->rays[ray_id].wall_hit_y = 0;
		data->rays[ray_id].wall_hit_content = 0;
		data->rays[ray_id].was_hit_vertical = 0;
		ray_id ++;
	}
}

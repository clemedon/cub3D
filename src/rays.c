/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:37:33 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 11:37:35 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_cast_ray(t_data *data, float ray_angle, t_ray *ray)
{
	t_cast	c;

	ray_angle = ft_normalize_angle(ray_angle);
	ft_get_ray_orientation(&c, ray_angle);
	ft_horizontal_step(data, ray_angle, &c);
	ft_horizontal_hit(data, &c);
	ft_vertical_step(data, ray_angle, &c);
	ft_vertical_hit(data, &c);
	ft_set_dist(data, &c);
	ft_dist_cmp(&c, ray, ray_angle);
}

void	ft_cast_all_rays(t_data *data)
{
	float	ray_angle;
	int		ray_id;

	ray_id = 0;
	while (ray_id < NUM_RAYS)
	{
		ray_angle = data->player.rotation_angle
			+ atan((ray_id - NUM_RAYS / 2) / ((WIN_WIDTH / 2) / tan(FOV / 2)));
		ft_cast_ray(data, ray_angle, &data->rays[ray_id]);
		ray_id ++;
	}
}

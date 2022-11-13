/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:23:09 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 11:30:14 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

float	ft_dist(float p_x, float p_y, float hit_x, float hit_y)
{
	return (sqrt((hit_x - p_x) * (hit_x - p_x)
			+ (hit_y - p_y) * (hit_y - p_y)));
}

void	ft_get_ray_orientation(t_cast *c, float ray_angle)
{
	c->ray_facing_down = 0;
	c->ray_facing_up = 0;
	c->ray_facing_left = 0;
	c->ray_facing_right = 0;
	if (ray_angle > 0 && ray_angle < PI)
		c->ray_facing_down = 1;
	else
		c->ray_facing_up = !c->ray_facing_down;
	if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
		c->ray_facing_right = 1;
	else
		c->ray_facing_left = !c->ray_facing_right;
}

void	ft_set_dist(t_data *data, t_cast *c)
{
	if (c->horizontal_hit)
		c->horizontal_dist = ft_dist(data->player.x, data->player.y,
				c->horizontal_hit_x, c->horizontal_hit_y);
	else
		c->horizontal_dist = (float)INT_MAX;
	if (c->vertical_hit)
		c->vertical_dist = ft_dist(data->player.x, data->player.y,
				c->vertical_hit_x, c->vertical_hit_y);
	else
		c->vertical_dist = (float)INT_MAX;
}

void	ft_dist_cmp(t_cast *c, t_ray *ray, float ray_angle)
{
	if (c->vertical_dist < c->horizontal_dist)
	{
		ray->distance = c->vertical_dist;
		ray->wall_hit_x = c->vertical_hit_x;
		ray->wall_hit_y = c->vertical_hit_y;
		ray->was_hit_vertical = 1;
		ray->wall_hit_content = c->vertical_content;
	}
	else
	{
		ray->distance = c->horizontal_dist;
		ray->wall_hit_x = c->horizontal_hit_x;
		ray->wall_hit_y = c->horizontal_hit_y;
		ray->was_hit_vertical = 0;
		ray->wall_hit_content = c->horizontal_content;
	}
	ray->ray_angle = ray_angle;
	ray->ray_facing_down = c->ray_facing_down;
	ray->ray_facing_up = c->ray_facing_up;
	ray->ray_facing_left = c->ray_facing_left;
	ray->ray_facing_right = c->ray_facing_right;
}

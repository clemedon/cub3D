/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:31:42 by athirion          #+#    #+#             */
/*   Updated: 2022/11/15 11:06:26 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_is_wall(t_data *data, float x, float y)
{
	float	map_x;
	float	map_y;

	if (x < 0 || x > data->cub.width * TILE_SIZE
		|| y < 0 || y > data->cub.height * TILE_SIZE)
		return (1);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x > data->cub.width - 1)
		return (1);
	if (map_y > data->cub.height - 1)
		return (1);
	return (data->cub.map[(int)map_y][(int)map_x] == 1);
}

void	ft_horizontal_step(t_data *data, float ray_angle, t_cast *c)
{
	c->horizontal_hit = 0;
	c->horizontal_hit_x = 0;
	c->horizontal_hit_y = 0;
	c->horizontal_content = 0;
	c->y_inter = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (c->ray_facing_down)
		c->y_inter += TILE_SIZE;
	c->x_inter = data->player.x
		+ (c->y_inter - data->player.y) / tan(ray_angle);
	c->y_step = TILE_SIZE;
	if (c->ray_facing_up)
		c->y_step *= -1;
	c->x_step = TILE_SIZE / tan(ray_angle);
	if (c->ray_facing_left && c->x_step > 0)
		c->x_step *= -1;
	if (c->ray_facing_right && c->x_step < 0)
		c->x_step *= -1;
}

void	ft_horizontal_hit(t_data *data, t_cast *c)
{
	c->next_horizontal_x = c->x_inter;
	c->next_horizontal_y = c->y_inter;
	while (c->next_horizontal_x >= 0 && c->next_horizontal_y >= 0)
	{
		c->current_x = c->next_horizontal_x;
		c->current_y = c->next_horizontal_y;
		if (c->ray_facing_up)
			c->current_y --;
		else
			c->current_y = c->next_horizontal_y;
		if (ft_is_wall(data, c->current_x, c->current_y))
		{
			c->horizontal_hit_x = c->next_horizontal_x;
			c->horizontal_hit_y = c->next_horizontal_y;
			c->horizontal_content = 1;
			c->horizontal_hit = 1;
			break ;
		}
		else
		{
			c->next_horizontal_x += c->x_step;
			c->next_horizontal_y += c->y_step;
		}
	}
}

void	ft_vertical_step(t_data *data, float ray_angle, t_cast *c)
{
	c->vertical_hit = 0;
	c->vertical_hit_x = 0;
	c->vertical_hit_y = 0;
	c->vertical_content = 0;
	c->x_inter = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (c->ray_facing_right)
		c->x_inter += TILE_SIZE;
	c->y_inter = data->player.y
		+ (c->x_inter - data->player.x) * tan(ray_angle);
	c->x_step = TILE_SIZE;
	if (c->ray_facing_left)
		c->x_step *= -1;
	c->y_step = TILE_SIZE * tan(ray_angle);
	if (c->ray_facing_up && c->y_step > 0)
		c->y_step *= -1;
	if (c->ray_facing_down && c->y_step < 0)
		c->y_step *= -1;
}

void	ft_vertical_hit(t_data *data, t_cast *c)
{
	c->next_vertical_x = c->x_inter;
	c->next_vertical_y = c->y_inter;
	while (c->next_vertical_x >= 0 && c->next_vertical_y >= 0)
	{
		c->current_x = c->next_vertical_x;
		c->current_y = c->next_vertical_y;
		if (c->ray_facing_left)
			c->current_x --;
		c->current_y = c->next_vertical_y;
		if (ft_is_wall(data, c->current_x, c->current_y))
		{
			c->vertical_hit_x = c->next_vertical_x;
			c->vertical_hit_y = c->next_vertical_y;
			c->vertical_content = 1;
			c->vertical_hit = 1;
			break ;
		}
		else
		{
			c->next_vertical_x += c->x_step;
			c->next_vertical_y += c->y_step;
		}
	}
}

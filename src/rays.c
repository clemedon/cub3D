#include "cube.h"

static float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

static float	ft_dist(float player_x, float player_y, float hit_x, float hit_y)
{
	return (sqrt((hit_x - player_x) * (hit_x - player_x)
			+ (hit_y - player_y) * (hit_y - player_y)));
}

static void	ft_get_ray_orientation(t_cast *c, float ray_angle)
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

static void	ft_horizontal_step(t_data *data, float ray_angle, t_cast *c)
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

static void	ft_horizontal_hit(t_data *data, t_cast *c)
{
	c->next_horizontal_x = c->x_inter;
	c->next_horizontal_y = c->y_inter;
	while (c->next_horizontal_x >= 0 && c->next_horizontal_x < WIN_WIDTH
		&& c->next_horizontal_y >= 0 && c->next_horizontal_y < WIN_HEIGHT)
	{
		c->current_x = c->next_horizontal_x;
		c->current_y = c->next_horizontal_y;
		if (c->ray_facing_up)
			c->current_y --;
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

static void	ft_vertical_step(t_data *data, float ray_angle, t_cast *c)
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

static void	ft_vertical_hit(t_data *data, t_cast *c)
{
	c->next_vertical_x = c->x_inter;
	c->next_vertical_y = c->y_inter;
	while (c->next_vertical_x >= 0 && c->next_vertical_x < WIN_WIDTH
		&& c->next_vertical_y >= 0 && c->next_vertical_y < WIN_HEIGHT)
	{
		c->current_x = c->next_vertical_x;
		c->current_y = c->next_vertical_y;
		if (c->ray_facing_left)
			c->current_x --;
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

static void	ft_set_dist(t_data *data, t_cast *c)
{
	if (c->horizontal_hit)
		c->horizontal_dist = ft_dist(data->player.x, data->player.y,
				c->horizontal_hit_x, c->horizontal_hit_y);
	else
		c->horizontal_dist = FLT_MAX;
	if (c->vertical_hit)
		c->vertical_dist = ft_dist(data->player.x, data->player.y,
				c->vertical_hit_x, c->vertical_hit_y);
	else
		c->vertical_dist = FLT_MAX;
}

static void	ft_dist_cmp(t_cast *c, t_ray *ray, float ray_angle)
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

	ray_angle = data->player.rotation_angle - (FOV / 2);
	ray_id = 0;
	while (ray_id < NUM_RAYS)
	{
		ft_cast_ray(data, ray_angle, &data->rays[ray_id]);
		ray_angle += FOV / NUM_RAYS;
		ray_id ++;
	}
}

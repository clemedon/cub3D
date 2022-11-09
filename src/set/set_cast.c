#include "cube.h"

void	ft_set_cast(t_data *data, t_ray *ray, t_proj *p, t_tex *tex)
{
	p->perpendicular_dist = ray->distance
		* cos(ray->ray_angle - data->player.rotation_angle);
	p->dist_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
	p->proj_wall_height = (TILE_SIZE / p->perpendicular_dist)
		* p->dist_proj_plane;
	p->wall_strip_height = (int)p->proj_wall_height;
	p->top_wall.y = (WIN_HEIGHT / 2) - (p->wall_strip_height / 2);
	if (p->top_wall.y < 0)
		p->top_wall.y = 0;
	p->bottom_wall.y = (WIN_HEIGHT / 2) + (p->wall_strip_height / 2);
	if (ray->was_hit_vertical)
		p->offset[0] = (int)ray->wall_hit_y % tex->w;
	else
		p->offset[0] = (int)ray->wall_hit_x % tex->w;
	p->y = p->top_wall.y;
	if (p->bottom_wall.y > WIN_HEIGHT)
		p->bottom_wall.y = WIN_HEIGHT;
}

#include "cube.h"

void	ft_3d_projection(t_data *data)
{
	int		i;
	float	wall_strip_height;
	float	dist_proj_plane;
	float	proj_wall_height;
	float	perpendicular_dist;
	t_point	top_wall;
	t_point	bottom_wall;
	t_point top_ceiling;
	t_point bottom_ceiling;
	t_point	top_floor;
	t_point	bottom_floor;

	i = 0;
	while (i < NUM_RAYS)
	{
		perpendicular_dist = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player.rotation_angle);
		dist_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
		proj_wall_height = (TILE_SIZE / perpendicular_dist) * dist_proj_plane;
		wall_strip_height = (int)proj_wall_height;
		top_wall.x = i;
		top_ceiling.x = i;
		top_floor.x = i;
		bottom_wall.x = i;
		bottom_ceiling.x = i;
		bottom_floor.x = i;
		top_wall.y = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
		if (top_wall.y < 0)
			top_wall.y = 0;
		bottom_wall.y = (WIN_HEIGHT / 2) + (wall_strip_height / 2);
		if (bottom_wall.y > WIN_HEIGHT)
			bottom_wall.y = WIN_HEIGHT;
		if (data->rays[i].was_hit_vertical)
			top_wall.color = 0xFFFFFF;
		else
			top_wall.color = 0xD4D2CD;
		bottom_wall.color = top_wall.color;
		top_ceiling.color = 0x94b5b3;
		bottom_ceiling.color = top_ceiling.color;
		top_floor.color = 0x262624;
		bottom_floor.color = top_floor.color;
		top_ceiling.y = 0;
		bottom_ceiling.y = top_wall.y;
		top_floor.y = bottom_wall.y;
		bottom_floor.y = WIN_HEIGHT;
		ft_draw_line(&data->mlx, top_floor, bottom_floor);
		ft_draw_line(&data->mlx, top_ceiling, bottom_ceiling);
		ft_draw_line(&data->mlx, top_wall, bottom_wall);
		i ++;
	}
}



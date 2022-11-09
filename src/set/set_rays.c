#include "cube.h"

void	ft_set_rays(t_data *data)
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


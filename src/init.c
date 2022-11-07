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

void	ft_init_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	data->mlx.img_ptr = NULL;
	/* ft_init_texture(data, &data->cub); */
}

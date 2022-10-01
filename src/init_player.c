#include "cube.h"

void	get_player_position(t_data *data)
{
	float	i;
	float	j;

	i = 0;
	while (i < data->cub.height)
	{
		j = 0;
		while (j < data->cub.width)
		{
			if (data->cub.map[(int) i][(int) j] > 1)
			{
				data->player.x = (float) j * TILE_SIZE + TILE_SIZE / 2;
				data->player.y = (float) i * TILE_SIZE + TILE_SIZE / 2;
				data->player.d_start = data->cub.map[(int) i][(int) j];
				return ;
			}
			j ++;
		}
		i ++;
	}
}

void	get_player_orientation(t_data *data)
{
	if (data->player.d_start == N)
		data->player.rotation_angle = -PI / 2;
	else if (data->player.d_start == S)
		data->player.rotation_angle = PI / 2;
	else if (data->player.d_start == E)
		data->player.rotation_angle = -PI;
	else if (data->player.d_start == W)
		data->player.rotation_angle = PI;
}

void	init_player(t_data *data)
{
	get_player_position(data);
	data->player.dx = 0;
	data->player.dy = 0;
	get_player_orientation(data);
	data->player.width = 1;
	data->player.height = 1;
	data->player.walk_direction = 0;
	data->player.side_direction = 0;
	data->player.turn_direction = 0;
	data->player.walk_speed = 0.1;
	data->player.turn_speed = 0.1;
}

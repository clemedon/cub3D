#include "cube.h"

int	ft_is_wall(t_data *data, float x, float y)
{
	float	map_x;
	float	map_y;

	if (x < 0 || x > data->cub.width * TILE_SIZE
		|| y < 0 || y > data->cub.height * TILE_SIZE)
		return (0);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	return (data->cub.map[(int)map_y][(int)map_x] == 1);
}

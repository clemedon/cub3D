#include "cube.h"

void	ft_set_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	data->mlx.img_ptr = NULL;
	/* ft_set_texture(data, &data->cub); */
}

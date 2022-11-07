#include "cube.h"

void	ft_quit(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_destroy_display(data->mlx.mlx_ptr); // OS
	free(data->mlx.mlx_ptr);
	free(n_texture);
	free(s_texture);
	free(w_texture);
	free(e_texture);
	exit(0);
}

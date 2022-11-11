#include "cube.h"

void	ft_quit(t_data *data)
{
	ft_free_cub (&data->cub);
	ft_free_texture (&data->cub, &data->mlx);
	ft_free_mlx (&data->mlx);
	exit(EXIT_SUCCESS);
}

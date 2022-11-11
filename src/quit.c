#include "cube.h"

void	ft_quit(t_data *data)
{
	int	i;

	i = 0;
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	while (i < 4)
	{
		if (data->cub.texture[i].img)
			mlx_destroy_image(data->mlx.mlx_ptr, data->cub.texture[i].img);
		i ++;
	}
	ft_free_texture (&data->cub);
	mlx_destroy_display(data->mlx.mlx_ptr); // OS
	ft_free(data->mlx.mlx_ptr);
	ft_freetab ((void **)data->cub.map);	
	exit(EXIT_SUCCESS);
}

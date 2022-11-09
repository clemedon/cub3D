#include "cube.h"

void	ft_set_tex(t_data *data, t_cub *cub)
{
	int		i;

	cub->tex[EA].path = cub->e_texture;
	cub->tex[WE].path = cub->w_texture;
	cub->tex[SO].path = cub->s_texture;
	cub->tex[NO].path = cub->n_texture;
	i = 0;
	while (i < 4)
	{
		cub->tex[i].img = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
				cub->tex[i].path,
				&cub->tex[i].w,
				&cub->tex[i].h);
		cub->tex[i].addr = mlx_get_data_addr(cub->tex[i].img,
				&cub->tex[i].bpp,
				&cub->tex[i].line_length,
				&cub->tex[i].endian);
		i++;
	}
}

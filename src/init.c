#include "cube.h"

void	ft_init_cub_color(t_cub *cub, const char **specs)
{
	(void)specs;
	cub->f_color_hex = 0;
	cub->c_color_hex = 0;
}

void	ft_init_cub_texture(t_cub *cub, const char **specs)
{
	(void)specs;
	cub->n_texture_fd = 0;
	cub->s_texture_fd = 0;
	cub->w_texture_fd = 0;
	cub->e_texture_fd = 0;
}

void	ft_init_cub_map(t_cub *cub, const char **specs)
{
	(void)specs;
	cub->map = 0;
	cub->width = 0;
	cub->height = 0;
}

void	ft_init_cub(t_cub *cub, const char **specs)
{
	cub->specs = specs;
	if (!ft_check_cub (specs))
	{
		ft_freetab ((void **)specs);
		ft_exit_error (__func__, ER_SPECS);
	}
	ft_init_cub_color (cub, specs);
	ft_init_cub_texture (cub, specs);
	ft_init_cub_map (cub, specs);
}

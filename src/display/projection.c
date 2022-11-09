#include "cube.h"

static void	ft_draw_ceiling(t_data *data)
{
	t_point	ceiling;

	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.color = data->cub.c_color_hex;
	ft_draw_rect(data, ceiling, WIN_WIDTH, WIN_HEIGHT / 2);
}

static void	ft_draw_floor(t_data *data)
{
	t_point	floor;

	floor.x = 0;
	floor.y = WIN_HEIGHT / 2;
	floor.color = data->cub.f_color_hex;
	ft_draw_rect(data, floor, WIN_WIDTH, WIN_HEIGHT / 2);
}

static t_tex	ft_choose_texture(t_ray *ray, t_cub *cub)
{
	if (ray->was_hit_vertical && ray->ray_facing_right)
		return (cub->tex[EA]);
	else if (ray->was_hit_vertical && ray->ray_facing_left)
		return (cub->tex[WE]);
	else if (!ray->was_hit_vertical && ray->ray_facing_up)
		return (cub->tex[NO]);
	else
		return (cub->tex[SO]);
}

void	ft_3d_projection(t_data *data)
{
	int		i;
	t_proj	p;
	t_tex	tex;

	i = 0;
	ft_draw_ceiling(data);
	ft_draw_floor(data);
	while (i < NUM_RAYS)
	{
		tex = ft_choose_texture(&data->rays[i], &data->cub);
		ft_set_cast(data, &data->rays[i], &p, &tex);
		while (p.y < p.bottom_wall.y)
		{
			p.dist_top = p.y + (p.wall_strip_height / 2) - (WIN_HEIGHT / 2);
			p.offset[1] = p.dist_top * ((float)tex.w / p.wall_strip_height);
			tex.texel = tex.addr + (p.offset[1]
					* tex.line_length + p.offset[0] * (tex.bpp / 8));
			ft_my_mlx_pixel_put(&data->mlx, i, p.y, *(int *)tex.texel);
			p.y++;
		}
		i ++;
	}
}

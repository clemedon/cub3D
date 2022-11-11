#include "cube.h"

void	ft_draw_ceiling(t_data *data)
{
	t_point	ceiling;

	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.color = data->cub.c_color_hex;
	ft_draw_rect(data, ceiling, WIN_WIDTH, WIN_HEIGHT / 2);
}

void	ft_draw_floor(t_data *data)
{
	t_point	floor;

	floor.x = 0;
	floor.y = WIN_HEIGHT / 2;
	floor.color = data->cub.f_color_hex;
	ft_draw_rect(data, floor, WIN_WIDTH, WIN_HEIGHT / 2);
}

void	ft_init_cast(t_data *data, t_ray *ray, t_proj *p, t_text *texture)
{
	p->perpendicular_dist = ray->distance
		* cos(ray->ray_angle - data->player.rotation_angle);
	p->dist_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
	p->proj_wall_height = (TILE_SIZE / p->perpendicular_dist)
		* p->dist_proj_plane;
	p->wall_strip_height = (int)p->proj_wall_height;
	p->top_wall.y = (WIN_HEIGHT / 2) - (p->wall_strip_height / 2);
	if (p->top_wall.y < 0)
		p->top_wall.y = 0;
	p->bottom_wall.y = (WIN_HEIGHT / 2) + (p->wall_strip_height / 2);
	if (ray->was_hit_vertical)
		p->offset[0] = (int)ray->wall_hit_y % texture->w;
	else
		p->offset[0] = (int)ray->wall_hit_x % texture->w;
	p->y = p->top_wall.y;
	if (p->bottom_wall.y > WIN_HEIGHT)
		p->bottom_wall.y = WIN_HEIGHT;
}

t_text	ft_choose_texture(t_ray *ray, t_cub *cub)
{
	if (ray->was_hit_vertical && ray->ray_facing_right)
		return (cub->texture[EA]);
	else if (ray->was_hit_vertical && ray->ray_facing_left)
		return (cub->texture[WE]);
	else if (!ray->was_hit_vertical && ray->ray_facing_up)
		return (cub->texture[NO]);
	else
		return (cub->texture[SO]);
}

//TODO
void	ft_init_texture(t_data *data, t_cub *cub)
{
	int		i;

	cub->texture[EA].path = cub->e_texture;
	cub->texture[WE].path = cub->w_texture;
	cub->texture[SO].path = cub->s_texture;
	cub->texture[NO].path = cub->n_texture;
	i = 0;
	while (i < 4)
	{
		cub->texture[i].img = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
				cub->texture[i].path,
				&cub->texture[i].w,
				&cub->texture[i].h);
		if (!cub->texture[i].img)
		{
			/* free... */
			exit(EXIT_FAILURE);
		}
		cub->texture[i].addr = mlx_get_data_addr(cub->texture[i].img,
				&cub->texture[i].bpp,
				&cub->texture[i].line_length,
				&cub->texture[i].endian);
		if (!cub->texture[i].addr)
		{
			/* free... */
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_3d_projection(t_data *data)
{
	int		i;
	t_proj	p;
	t_text	texture;

	i = 0;
	ft_draw_ceiling(data);
	ft_draw_floor(data);
	while (i < NUM_RAYS)
	{
		texture = ft_choose_texture(&data->rays[i], &data->cub);
		ft_init_cast(data, &data->rays[i], &p, &texture);
		while (p.y < p.bottom_wall.y)
		{
			p.dist_top = p.y + (p.wall_strip_height / 2) - (WIN_HEIGHT / 2);
			p.offset[1] = p.dist_top * ((float)texture.w / p.wall_strip_height);
			texture.texel = texture.addr + (p.offset[1]
					* texture.line_length + p.offset[0] * (texture.bpp / 8));
			ft_my_mlx_pixel_put(&data->mlx, i, p.y, *(int *)texture.texel);
			p.y++;
		}
		i ++;
	}
}

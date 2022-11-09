#include "cube.h"

void	ft_draw_mini_map(t_data *data)
{
	t_point	p;
	int		i;
	int		j;

	p.x = 0;
	p.y = 0;
	p.color = 0xFFFFFF;
	i = -1;
	ft_draw_rect(data, p, TILE_SIZE * MAP_SCALE * data->cub.width,
		TILE_SIZE * MAP_SCALE * data->cub.height);
	p.color = data->cub.f_color_hex;
	while (++i < data->cub.height)
	{
		j = -1;
		p.x = 0;
		while (++j < data->cub.width)
		{
			if (data->cub.map[i][j] == 1)
				ft_draw_rect(data, p, TILE_SIZE * MAP_SCALE,
					TILE_SIZE * MAP_SCALE);
			p.x += TILE_SIZE * MAP_SCALE;
		}
		p.y += TILE_SIZE * MAP_SCALE;
	}
}

void	ft_draw_player(t_data *data)
{
	t_point	p;

	p.x = round (data->player.x * MAP_SCALE);
	p.y = round (data->player.y * MAP_SCALE);
	p.color = 0x00FF00;
	ft_draw_circle(data, p, 2);
}

void	ft_draw_rays(t_data *data)
{
	int		i;
	t_point	p_start;
	t_point	p_end;

	i = 0;
	p_start.x = data->player.x * MAP_SCALE;
	p_start.y = data->player.y * MAP_SCALE;
	p_start.color = 0x00FF00;
	p_end.color = p_start.color;
	while (i < NUM_RAYS)
	{
		p_end.x = round(data->rays[i].wall_hit_x * MAP_SCALE);
		p_end.y = round(data->rays[i].wall_hit_y * MAP_SCALE);
		ft_draw_line(&data->mlx, p_start, p_end);
		i += 80;
	}
}

int	ft_render(t_data *data)
{
	if (data->mlx.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img_ptr,
			&data->mlx.bpp, &data->mlx.line_length, &data->mlx.endian);
	ft_cast_all_rays(data);
	ft_3d_projection(data);
	if (data->cub.minimap == 1)
	{
		ft_draw_mini_map(data);
		ft_draw_player(data);
		if (data->cub.ray == 1)
			ft_draw_rays(data);
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.img_ptr, 0, 0);
	return (0);
}

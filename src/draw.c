#include "cube.h"

void	ft_my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(int *) dst = color;
}

void	ft_draw_line(t_mlx *mlx, t_point begin, t_point end)
{
	t_point	delta;
	t_point	point;
	int		pixel;

	delta.x = fabs(end.x - begin.x);
	delta.y = fabs(end.y - begin.y);
	pixel = sqrt(delta.x * delta.x + delta.y * delta.y);
	delta.x /= (float) pixel;
	delta.y /= (float) pixel;
	point.x = begin.x;
	point.y = begin.y;
	point.color = begin.color;
	while (pixel)
	{
		if (point.x >= 0 && point.x < WIN_WIDTH
			&& point.y >= 0 && point.y < WIN_HEIGHT)
			ft_my_mlx_pixel_put(mlx, point.x, point.y, point.color);
		if (begin.x < end.x)
			point.x += delta.x;
		else
			point.x -= delta.x;
		if (begin.y < end.y)
			point.y += delta.y;
		else
			point.y -= delta.y;
		pixel --;
	}
}

void	ft_draw_rect(t_data *data, t_point start, int width, int height)
{
	int		i;
	t_point	end;

	i = 0;
	end.x = start.x + width;
	end.y = start.y;
	while (i < height)
	{
		end.y = start.y;
		ft_draw_line(&data->mlx, start, end);
		start.y ++;
		i ++;
	}
}

void	ft_draw_mini_map(t_data *data)
{
	t_point	p;
	int		i;
	int		j;

	p.y = 0;
	i = 0;
	while (i < ROWS)
	{
		j = 0;
		p.x = 0;
		while (j < COLS)
		{
			if (data->cub.map[i][j] == 1)
				p.color = 0xD4D2CD;
			else
				p.color = 0x262624;
			if (p.x >= 0 && p.x < (COLS * TILE_SIZE)
				&& p.y >= 0 && p.y < (ROWS * TILE_SIZE))
				ft_draw_rect(data, p, TILE_SIZE * MAP_SCALE,
					TILE_SIZE * MAP_SCALE);
			j ++;
			p.x += TILE_SIZE * MAP_SCALE;
		}
		p.y += TILE_SIZE * MAP_SCALE;
		i ++;
	}
}

void	ft_draw_grid(t_data *data)
{
	t_point start;
	t_point end;
	int		y;
	int		x;

	start.x = 0;
	start.y = 0;
	start.color = 0xFFFFFF;
	end.color = start.color;
	end.x = WIN_WIDTH - 1;
	end.y = 0;
	y = 0;
	x = 0;
	while (y < ROWS)
	{
		ft_draw_line(&data->mlx, start, end);
		start.y += TILE_SIZE;
		end.y += TILE_SIZE;
		y ++;
	}
	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = WIN_HEIGHT;
	while (x < COLS)
	{
		ft_draw_line(&data->mlx, start, end);
		start.x += TILE_SIZE;
		end.x += TILE_SIZE;
		x ++;
	}
}

void	ft_draw_rays(t_data *data)
{
	int		i;
	t_point	p_start;
	t_point p_end;
	i = 0;

	p_start.x = data->player.x * MAP_SCALE;
	p_start.y = data->player.y * MAP_SCALE;
	p_start.color = 0x94B5B3;
	p_end.color = p_start.color;
	while (i < NUM_RAYS)
	{
		p_end.x = data->rays[i].wall_hit_x * MAP_SCALE;
		p_end.y = data->rays[i].wall_hit_y * MAP_SCALE;
		ft_draw_line(&data->mlx, p_start, p_end);
		i ++;
	};
}

void	ft_draw_player(t_data *data)
{
	t_point	p_start;
	t_point	p_end;
	t_point	temp;

	p_start.x = data->player.x * MAP_SCALE;
	p_start.y = data->player.y * MAP_SCALE;
	p_start.color = 0x0000FF;
		p_end.x = p_start.x + cos(data->player.rotation_angle) * 40;
	p_end.y = p_start.y + sin(data->player.rotation_angle) * 40;
	p_end.color = p_start.color;
	temp = p_start;
	temp.color = 0x00FF00;
	ft_draw_line(&data->mlx, p_start, p_end);
	ft_draw_rect(data, temp, data->player.width, data->player.height);
}

int	ft_render(t_data *data)
{
	/* mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr); */
	if (data->mlx.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img_ptr,
			&data->mlx.bpp, &data->mlx.line_length, &data->mlx.endian);
	ft_cast_all_rays(data);
	ft_3d_projection(data);
	/* ft_draw_mini_map(data); */
	/* ft_draw_grid(data); */
	/* ft_draw_player(data); */
	/* ft_draw_rays(data); */
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.img_ptr, 0, 0);
	return (0);
}

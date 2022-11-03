#include "cube.h"

void	ft_3d_projection(t_data *data)
{
	int		i;
	float	wall_strip_height;
	float	dist_proj_plane;
	float	proj_wall_height;
	float	perpendicular_dist;
	t_point	top_wall;
	t_point	bottom_wall;
	t_point top_ceiling;
	t_point bottom_ceiling;
	t_point	top_floor;
	t_point	bottom_floor;
	t_img	texture;
	
	texture.path = "resources/walkstone.xpm";
	texture.img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, texture.path, &texture.width, &texture.width);
	char	*texel;
	texture.addr =  mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_length, &texture.endian);
	int		y;
	int		offset[2];
	int		dist_top;

	i = 0;
	while (i < NUM_RAYS)
	{
		perpendicular_dist = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player.rotation_angle);
		dist_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
		proj_wall_height = (TILE_SIZE / perpendicular_dist) * dist_proj_plane;
		wall_strip_height = (int)proj_wall_height;
		top_wall.x = i;
		top_ceiling.x = i;
		top_floor.x = i;
		bottom_wall.x = i;
		bottom_ceiling.x = i;
		bottom_floor.x = i;
		top_wall.y = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
		if (top_wall.y < 0)
			top_wall.y = 0;
		bottom_wall.y = (WIN_HEIGHT / 2) + (wall_strip_height / 2);
		if (data->rays[i].was_hit_vertical)
			offset[0] = ((int)data->rays[i].wall_hit_y % texture.width);
		else
			offset[0] = ((int)data->rays[i].wall_hit_x % texture.width);
		y = top_wall.y;
		if (bottom_wall.y > WIN_HEIGHT)
			bottom_wall.y = WIN_HEIGHT;

		while (y < bottom_wall.y)
		{
			dist_top = y + (wall_strip_height / 2) - (WIN_HEIGHT / 2);
			offset[1] = dist_top * ((float)texture.width / wall_strip_height);
			/* printf("offset[1] [%d]\n", offset[1]); */
			/* printf("offset[0] [%d]\n", offset[0]); */
			texel = texture.addr + (offset[1] * texture.line_length + offset[0] * (texture.bpp / 8));
			/* printf("%s\n", texel); */
			/* printf("%d\n", data->mlx.line_length); */
			/* printf("%d\n", data->mlx.bpp); */
			/* printf("%d\n", texture.line_length); */
			/* printf("%d\n", texture.bpp); */
			/* ft_my_mlx_pixel_put(&data->mlx, i, y, 0xff0000); */
			ft_my_mlx_pixel_put(&data->mlx, i, y, *(int *)texel);
			y++;
		}
		/* if (data->rays[i].was_hit_vertical) */
		/* 	top_wall.color = 0xFFFFFF; */
		/* else */
		/* 	top_wall.color = 0xD4D2CD; */
		bottom_wall.color = top_wall.color;
		top_ceiling.color = data->cub.c_color_hex;
		bottom_ceiling.color = top_ceiling.color;
		top_floor.color = data->cub.f_color_hex;
		bottom_floor.color = top_floor.color;
		top_ceiling.y = 0;
		bottom_ceiling.y = top_wall.y;
		top_floor.y = bottom_wall.y;
		bottom_floor.y = WIN_HEIGHT;
		ft_draw_line(&data->mlx, top_floor, bottom_floor);
		ft_draw_line(&data->mlx, top_ceiling, bottom_ceiling);
		/* ft_draw_line(&data->mlx, top_wall, bottom_wall); */
		i ++;
	}
}



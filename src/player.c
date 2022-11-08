#include "cube.h"

int	ft_move(t_data *data)
{
	t_point	p;
	float	step;	

	p.x = data->player.x;
	p.y = data->player.y;
	data->player.rotation_angle += (data->player.turn_direction * (PI / 180));
	if (data->player.walk_direction && data->player.side_direction)
	{
		step = data->player.walk_direction * 5;
		p.x = data->player.x + data->player.side_direction * step * cos(data->player.rotation_angle + 45 * (PI/180));
		p.y = data->player.y + step * sin(data->player.rotation_angle + 45 * (PI/180));
	}
	else if (data->player.side_direction)
	{
		step = data->player.side_direction * 5;
		p.x = data->player.x + step * sin(data->player.rotation_angle);
		p.y = data->player.y - step * cos(data->player.rotation_angle);
	}
	else if (data->player.turn_direction || data->player.walk_direction)
	{
		step = data->player.walk_direction * 5;
		p.x = data->player.x + cos(data->player.rotation_angle) * step;
		p.y = data->player.y + sin(data->player.rotation_angle) * step;
	}
	
	if (!ft_is_wall(data, p.x, p.y))
	{
		data->player.x = p.x;
		data->player.y = p.y;
	}
	ft_render(data);
	return (0);
}

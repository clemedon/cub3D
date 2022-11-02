#include "cube.h"

void	ft_move_up(t_data *data)
{
	data->player.walk_direction = 1;
	ft_move_player(data);
}

void	ft_move_down(t_data *data)
{
	data->player.walk_direction = -1;
	ft_move_player(data);
}

void	ft_move_left(t_data *data)
{
	data->player.side_direction = -1;
	ft_side_move(data);
}

void	ft_move_right(t_data *data)
{
	data->player.side_direction = 1;
	ft_side_move(data);
}

void	ft_turn_left(t_data *data)
{
	data->player.turn_direction = -1;
	ft_move_player(data);
}

void	ft_turn_right(t_data *data)
{
	data->player.turn_direction = 1;
	ft_move_player(data);
}

void	ft_side_move(t_data *data)
{
	t_point	p;
	float	step;

	p.x = data->player.x;
	p.y = data->player.y;
	step = data->player.side_direction * 5;
	p.x = data->player.x + step * sin(data->player.rotation_angle);
	p.y = data->player.y - step * cos(data->player.rotation_angle);
	data->player.side_direction = 0;
	if (!ft_is_wall(data, p.x, p.y))
	{
		data->player.x = p.x;
		data->player.y = p.y;
	}
	ft_render(data);
}

void	ft_move_player(t_data *data)
{
	t_point	p;
	float	step;

	p.x = data->player.x;
	p.y = data->player.y;
	data->player.rotation_angle
		+= (data->player.turn_direction * (PI / 180));
	step = data->player.walk_direction * 5;
	p.x = data->player.x + cos(data->player.rotation_angle) * step;
	p.y = data->player.y + sin(data->player.rotation_angle) * step;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	if (!ft_is_wall(data, p.x, p.y))
	{
		data->player.x = p.x;
		data->player.y = p.y;
	}
	ft_render(data);
}

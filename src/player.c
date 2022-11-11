#include "cube.h"

void	ft_side_move(t_data *data, t_point *p)
{
	float	step;

	step = data->player.side_direction * 5;
	p->x = data->player.x + step * sin(data->player.rotation_angle);
	p->y = data->player.y - step * cos(data->player.rotation_angle);
}

void	ft_oblique_move(t_data *data, t_point *p)
{
	float	step;

	step = data->player.walk_direction * 5;
	if (data->player.side_direction == 1)
	{
		p->x = data->player.x + step
			* cos(data->player.rotation_angle - PI / 4);
		p->y = data->player.y + step
			* sin(data->player.rotation_angle - PI / 4);
	}
	else if (data->player.side_direction == -1)
	{
		p->x = data->player.x + step
			* cos(data->player.rotation_angle + PI / 4);
		p->y = data->player.y + step
			* sin(data->player.rotation_angle + PI / 4);
	}
}

void	ft_straight_move(t_data *data, t_point *p)
{
	float	step;

	step = data->player.walk_direction * 5;
	p->x = data->player.x + cos(data->player.rotation_angle) * step;
	p->y = data->player.y + sin(data->player.rotation_angle) * step;
}

int	ft_move_player(t_data *data)
{
	t_point	p;

	p.x = data->player.x;
	p.y = data->player.y;
	data->player.rotation_angle += (data->player.turn_direction * (PI / 180));
	if (data->player.walk_direction == 1 && data->player.side_direction)
		ft_oblique_move(data, &p);
	else if (!data->player.walk_direction && data->player.side_direction)
		ft_side_move(data, &p);
	else
		ft_straight_move(data, &p);
	if (!ft_is_wall(data, p.x, p.y))
	{
		data->player.x = p.x;
		data->player.y = p.y;
	}
	ft_render(data);
	return (0);
}

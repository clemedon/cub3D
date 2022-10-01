#include "cube.h"

void	ft_key_event(int key, t_data *data)
{
	if (key == ESCAPE)
		ft_close(data);
	else if (key == MOVE_FRONT)
		move_up(data);
	else if (key == MOVE_BACK)
		move_down(data);
	else if (key == MOVE_RIGHT)
		move_right(data);
	else if (key == MOVE_LEFT)
		move_left(data);
	else if (key == TURN_LEFT)
		turn_left(data);
	else if (key == TURN_RIGHT)
		turn_right(data);
}

void	ft_mouse_event(t_data *data)
{
	ft_close(data);
}

int	ft_waiting_event(t_data *data)
{
	(void) data;
	return (0);
}

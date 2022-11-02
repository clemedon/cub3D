#include "cube.h"

void	ft_key_event(int key, t_data *data)
{
	if (key == ESCAPE)
		ft_quit(data);
	else if (key == MOVE_FRONT)
		ft_move_up(data);
	else if (key == MOVE_BACK)
		ft_move_down(data);
	else if (key == MOVE_RIGHT)
		ft_move_right(data);
	else if (key == MOVE_LEFT)
		ft_move_left(data);
	else if (key == TURN_LEFT)
		ft_turn_left(data);
	else if (key == TURN_RIGHT)
		ft_turn_right(data);
}

void	ft_mouse_event(t_data *data)
{
	ft_quit(data);
}

int	ft_waiting_event(t_data *data)
{
	(void) data;
	return (0);
}

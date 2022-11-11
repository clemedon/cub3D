#include "cube.h"

static void	ft_check_arg(const char *arg)
{
	const char	*suffix = "x.cub";

	if (ft_strlen (arg) < ft_strlen (suffix))
		ft_exit_error (NULL, ER_USAGE);
	while (*(arg + 1))
		arg++;
	while (*(suffix + 1))
		suffix++;
	while (*(suffix + 1) != '.')
		if (*arg-- != *suffix--)
			ft_exit_error (NULL, ER_USAGE);
	if ((*arg) == '/')
		ft_exit_error (NULL, ER_USAGE);
}


int	main(int ac, char **argv)
{
	t_data	data;
	const char	**specs;

	if (ac == 2)
	{
		ft_check_arg (argv[1]);
		specs = ft_load_cub (argv[1]);
		if (!ft_check_cub (specs))
			return (FALSE);
		if (!ft_init (&data, specs))
			return (EXIT_FAILURE);
		ft_freetab ((void **)specs);
		ft_render(&data);
		mlx_hook(data.mlx.win_ptr, 2, 1L << 0, (void *)ft_key_event, &data);
		mlx_hook(data.mlx.win_ptr, 3, 1L << 1, (void *)ft_key_release, &data);
		mlx_hook(data.mlx.win_ptr, 17, 1L << 17, (void *)ft_mouse_event, &data);
		mlx_loop_hook(data.mlx.mlx_ptr, ft_move_player, &data);
		mlx_loop(data.mlx.mlx_ptr);
	}
	else
		ft_exit_error (NULL, ER_USAGE);
	return (0);
}

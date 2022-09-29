#include "cube.h"

void	ft_check_arg(const char *arg)
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
	t_cub	cub;

	if (ac == 2)
	{
		ft_check_arg (argv[1]);
		ft_init_cub (&cub, ft_load (argv[1]));
		ft_freetab ((void **)cub.specs);
	}
	else
		ft_exit_error (NULL, ER_USAGE);
	return (0);
}

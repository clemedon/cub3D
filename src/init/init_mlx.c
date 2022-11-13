/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:17:24 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 11:17:26 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_mlx(t_mlx *mlx)
{
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
		mlx_destroy_display(mlx->mlx_ptr);
	ft_free (mlx->mlx_ptr);
}

static void	ft_pre_init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img_ptr = NULL;
	mlx->addr = NULL;
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->line_length = 0;
}

int	ft_init_mlx(t_mlx *mlx)
{
	ft_pre_init_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (FALSE);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!mlx->win_ptr)
		return (FALSE);
	return (TRUE);
}

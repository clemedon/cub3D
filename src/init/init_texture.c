/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:15:53 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 11:15:54 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_texture(t_cub *cub, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->texture[i].img)
			mlx_destroy_image(mlx->mlx_ptr, cub->texture[i].img);
		ft_free (cub->texture[i].texel);
		i++;
	}
}

static void	ft_pre_init_texture(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->texture[i].img = NULL;
		cub->texture[i].addr = NULL;
		cub->texture[i].texel = NULL;
		cub->texture[i].bpp = 0;
		cub->texture[i].endian = 0;
		cub->texture[i].line_length = 0;
		cub->texture[i].w = 0;
		cub->texture[i].h = 0;
		cub->texture[i].path = NULL;
		i++;
	}
}

t_bool	ft_init_texture(t_cub *cub, t_mlx *mlx)
{
	int		i;

	ft_pre_init_texture(cub);
	cub->texture[EA].path = cub->e_texture;
	cub->texture[WE].path = cub->w_texture;
	cub->texture[SO].path = cub->s_texture;
	cub->texture[NO].path = cub->n_texture;
	i = 0;
	while (i < 4)
	{
		cub->texture[i].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
				cub->texture[i].path,
				&cub->texture[i].w,
				&cub->texture[i].h);
		if (!cub->texture[i].img)
			return (FALSE);
		cub->texture[i].addr = mlx_get_data_addr(cub->texture[i].img,
				&cub->texture[i].bpp,
				&cub->texture[i].line_length,
				&cub->texture[i].endian);
		if (!cub->texture[i].addr)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

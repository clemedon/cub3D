/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:22:08 by athirion          #+#    #+#             */
/*   Updated: 2022/11/13 11:22:09 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_quit(t_data *data)
{
	ft_free_cub (&data->cub);
	ft_free_texture (&data->cub, &data->mlx);
	ft_free_mlx (&data->mlx);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:19:28 by athirion          #+#    #+#             */
/*   Updated: 2022/11/15 11:02:52 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(int *) dst = color;
}

void	ft_draw_line(t_mlx *mlx, t_point begin, t_point end)
{
	t_point	delta;
	t_point	point;
	int		pixel;

	delta.x = fabs(end.x - begin.x);
	delta.y = fabs(end.y - begin.y);
	pixel = sqrt(delta.x * delta.x + delta.y * delta.y);
	delta.x /= (float) pixel;
	delta.y /= (float) pixel;
	point = begin;
	while (pixel)
	{
		if (point.x >= 0 && point.y >= 0
			&& point.x < WIN_WIDTH && point.y < WIN_HEIGHT)
			ft_my_mlx_pixel_put(mlx, point.x, point.y, point.color);
		if (begin.x < end.x)
			point.x += delta.x;
		else
			point.x -= delta.x;
		if (begin.y < end.y)
			point.y += delta.y;
		else
			point.y -= delta.y;
		pixel --;
	}
}

void	ft_draw_rect(t_mlx *mlx, t_point start, int width, int height)
{
	int		i;
	t_point	end;

	i = 0;
	end.x = start.x + width;
	end.y = start.y;
	while (i < height)
	{
		end.y = start.y;
		ft_draw_line(mlx, start, end);
		start.y ++;
		i ++;
	}
}

void	ft_draw_circle(t_mlx *mlx, t_point center, double radius)
{
	int		i;
	t_point	c;

	i = 0;
	while (radius)
	{
		i = 0;
		while (i < 360)
		{
			c.x = cos(i * (180 / PI)) * radius;
			c.y = sin(i * (180 / PI)) * radius;
			ft_my_mlx_pixel_put(mlx, center.x + c.x,
				center.y + c.y, center.color);
			i ++;
		}
		radius --;
	}
}

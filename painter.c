/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:55:23 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 16:55:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_painter(t_coord c, int dcolor, int error, t_map *map)
{
	int error2;
	int sx;
	int sy;

	sx = c.x1 < c.x2 ? 1 : -1;
	sy = c.yy1 < c.y2 ? 1 : -1;
	while (c.x1 != c.x2 || c.yy1 != c.y2)
	{
		mlx_pixel_put(map->mlx_ptr, map->window_ptr, c.x1, c.yy1, c.color1);
		c.color1 += c.color1 < c.color2 ? dcolor : -1 * dcolor;
		error2 = error * 2;
		if (error2 > -c.dy)
		{
			error -= c.dy;
			c.x1 += sx;
		}
		if (error2 < c.dx)
		{
			error += c.dx;
			c.yy1 += sy;
		}
	}
}

void	ft_bresenham(t_coord c, t_map *map)
{
	int dcolor;
	int error;

	c.dy = abs(c.y2 - c.yy1);
	c.dx = abs(c.x2 - c.x1);
	error = c.dx - c.dy;
	if (c.dx > c.dy)
		dcolor = c.dx ? (c.color1 ^ c.color2) / c.dx : 0;
	else
		dcolor = c.dy ? (c.color1 ^ c.color2) / c.dy : 0;
	mlx_pixel_put(map->mlx_ptr, map->window_ptr, c.x1, c.yy1, c.color1);
	ft_painter(c, dcolor, error, map);
	mlx_pixel_put(map->mlx_ptr, map->window_ptr, c.x2, c.y2, c.color2);
}

void	ft_draw_maps(t_map *map, int i, int j)
{
	t_coord	c;

	while (++i < map->sizey && (j = -1))
		while (++j < map->sizex)
		{
			c.x1 = (int)(map->xvalue)[i][j];
			c.yy1 = (int)(map->yvalue)[i][j];
			c.color1 = map->color[i][j];
			if (i < map->sizey - 1)
			{
				c.x2 = (int)(map->xvalue[i + 1][j]);
				c.y2 = (int)(map->yvalue[i + 1][j]);
				c.color2 = map->color[i + 1][j];
				ft_bresenham(c, map);
			}
			if (j < map->sizex - 1)
			{
				c.x2 = (int)(map->xvalue[i][j + 1]);
				c.y2 = (int)(map->yvalue[i][j + 1]);
				c.color2 = map->color[i][j + 1];
				ft_bresenham(c, map);
			}
		}
}

void	ft_draw_map(t_map *map)
{
	ft_calc_coord(map);
	map->sizey && map->sizey == 1 ? mlx_pixel_put(map->mlx_ptr, map->window_ptr,
		(int)map->xvalue[0][0], (int)map->yvalue[0][0], map->color[0][0]) : 0;
	ft_draw_maps(map, -1, 0);
}

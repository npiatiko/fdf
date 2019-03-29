#include "fdf.h"

void drawLine(t_coord c)
{
	const int deltaX = abs(c.x2 - c.x1);
	const int deltaY = abs(c.y2 - c.yy1);
	const int signX = c.x1 < c.x2 ? 1 : -1;
	const int signY = c.yy1 < c.y2 ? 1 : -1;
	int dcolor;
	int error;

	error = deltaX - deltaY;
	if (deltaX > deltaY)
	{
		dcolor = deltaX ? (c.color1 ^ c.color2) / deltaX : 0;
	}
	else
	{
		dcolor = deltaY ? (c.color1 ^ c.color2) / deltaY : 0;
	}
//	dcolor = deltaX > deltaY ? (c.color1 - c.color2) / deltaX : (c.color1 - c.color2) / deltaY;
//	mlx_pixel_put(g_mlx_ptr, g_window_ptr, c.x1, c.yy1, c.color1);
	while(c.x1 != c.x2 || c.yy1 != c.y2)
	{
		mlx_pixel_put(g_mlx_ptr, g_window_ptr, c.x1, c.yy1, c.color1);
		c.color1 += c.color1 < c.color2 ? dcolor : -1 * dcolor;
		const int error2 = error * 2;
		//
		if(error2 > -deltaY)
		{
			error -= deltaY;
			c.x1 += signX;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			c.yy1 += signY;
		}
	}
	mlx_pixel_put(g_mlx_ptr, g_window_ptr, c.x2, c.y2, c.color2);
}

void ft_draw_map(t_map *map)
{
	int		i;
	int		j;
	t_coord	c;

	i = -1;
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
				drawLine(c);
			}
			if (j < map->sizex - 1)
			{
				c.x2 = (int)(map->xvalue[i][j + 1]);
				c.y2 = (int)(map->yvalue[i][j + 1]);
				c.color2 = map->color[i][j + 1];
				drawLine(c);
			}
		}
}

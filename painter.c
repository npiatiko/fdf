#include "fdf.h"

void drawLine(t_coord c)
{
	const int deltaX = abs(c.i2 - c.i1);
	const int deltaY = abs(c.j2 - c.jj1);
	const int signX = c.i1 < c.i2 ? 1 : -1;
	const int signY = c.jj1 < c.j2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	mlx_pixel_put(g_mlx_ptr, g_window_ptr, c.i2, c.j2, c.color1);
	while(c.i1 != c.i2 || c.jj1 != c.j2)
	{
		mlx_pixel_put(g_mlx_ptr, g_window_ptr, c.i1, c.jj1, c.color1);

		const int error2 = error * 2;
		//
		if(error2 > -deltaY)
		{
			error -= deltaY;
			c.i1 += signX;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			c.jj1 += signY;
		}
	}
}

//int 	ft_scale(double value)
//{
//	return ((int)(value * g_scale));
//}
void ft_draw_map(t_map *map)
{
	int		i;
	int		j;
	t_coord	c;

	i = -1;
	while (++i < map->sizey && (j = -1))
		while (++j < map->sizex)
		{
			c.i1 = i;
			c.jj1 = j;
			c.color1 = map->color[i][j];
			if (i < map->sizey - 1)
			{
				c.i2 = (int)(map->xvalue[i + 1][j]);
				c.j2 = (int)(map->yvalue[i + 1][j]);
				c.color2 = map->color[i + 1][j];
				drawLine(c);
			}
			if (j < map->sizex - 1)
			{
				c.i2 = (int)(map->xvalue[i][j + 1]);
				c.j2 = (int)(map->yvalue[i][j + 1]);
				c.color2 = map->color[i][j + 1];
				drawLine(c);
			}
		}
}

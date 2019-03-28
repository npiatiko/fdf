#include "fdf.h"

void ft_reset_base_matrix(t_map *map)
{
	map->basematrix[0][0] = 1.0;
	map->basematrix[0][1] = 0.0;
	map->basematrix[0][2] = 0.0;
	map->basematrix[1][0] = 0.0;
	map->basematrix[1][1] = 1.0;
	map->basematrix[1][2] = 0.0;
	map->basematrix[2][0] = 0.0;
	map->basematrix[2][1] = 0.0;
	map->basematrix[2][2] = 1.0;
}

void	ft_init_rotmtrx(double **mtrx, int angle, char c)
{
	if (c == 'x')
	{
		mtrx[0][0] = 1.0;
		mtrx[1][1] = cos(angle * M_PI / 180);
		mtrx[2][2] = mtrx[1][1];
		mtrx[2][1] = sin(angle * M_PI / 180);
		mtrx[1][2] = -1.0 * mtrx[2][1];
	}
	else if (c == 'y')
	{
		mtrx[1][1] = 1.0;
		mtrx[0][0] = cos(angle * M_PI / 180);
		mtrx[2][2] = mtrx[0][0];
		mtrx[0][2] = sin(angle * M_PI / 180);
		mtrx[2][0] = -1.0 * mtrx[0][2];
	}
	else if (c == 'z')
	{
		mtrx[2][2] = 1.0;
		mtrx[0][0] = cos(angle * M_PI / 180);
		mtrx[1][1] = mtrx[0][0];
		mtrx[1][0] = sin(angle * M_PI / 180);
		mtrx[0][1] = -1.0 * mtrx[1][0];
	}
}
double	**ft_rotmx(int angle, char c)
{
	double	**mtrx;
	int		i;

	i = -1;
	mtrx = (double **)ft_memalloc(sizeof(double *) * 3);
	while (++i < 3)
		mtrx[i] = (double *)ft_memalloc(sizeof(double) * 3);
	ft_init_rotmtrx(mtrx, angle, c);
	return mtrx;
}

void ft_copymtrx(double mtrx[3][3], t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			mtrx[i][j] = map->basematrix[i][j];
		}
	}
}

void	ft_delmtrx(double **mtrx)
{
	free(mtrx[2]);
	free(mtrx[1]);
	free(mtrx[0]);
	free(mtrx);
}

void ft_multiple_mtrx(double **mtrx, t_map *map)
{
	double	tmp[3][3];
	int 	i;
	int 	j;


	ft_copymtrx(tmp, map);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			map->basematrix[i][j] = tmp[i][0] * mtrx[0][j]
				+ tmp[i][1] * mtrx[1][j] + tmp[i][2] * mtrx[2][j];
//			map->basematrix[i][j] *= map->params->scale;
		}
	}
	ft_delmtrx(mtrx);
}

void ft_calc_mtrx(t_map *map)
{
	double	**scaler;
	int		i;

	i = -1;
	scaler = (double **)ft_memalloc(sizeof(double *) * 3);
	while (++i < 3)
	{
		scaler[i] = (double *) ft_memalloc(sizeof(double) * 3);
		scaler[i][i] = map->params->scale;
	}
	ft_multiple_mtrx(ft_rotmx(map->params->anglex, 'x'), map);
	ft_multiple_mtrx(ft_rotmx(map->params->angley, 'y'), map);
	ft_multiple_mtrx(ft_rotmx(map->params->anglez, 'z'), map);
	ft_multiple_mtrx(scaler, map);
}

void ft_calc_coord(t_map *map)
{
	int	i;
	int	j;

	ft_reset_base_matrix(map);
	ft_calc_mtrx(map);
	i = -1;
	while (++i < map->sizey)
	{
		j = -1;
		while (++j < map->sizex)
		{
			(map->xvalue)[i][j] = (map->basematrix[0][0] * (j) + map->basematrix[0][1]
		 * (i) + map->basematrix[0][2] * map->altitude[i][j]);
			(map->xvalue)[i][j] += map->params->xshift;
			(map->yvalue)[i][j] =(map->basematrix[1][0] * (j) + map->basematrix[1][1]
		 * (i) + map->basematrix[1][2] * map->altitude[i][j]);
			(map->yvalue)[i][j] += map->params->yshift;
		}
	}
}

void	ft_printmatrix(double mtrx[3][3])
{
	int i = -1;
	int j;

	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			ft_printf("%10.5f  ", mtrx[i][j]);
		ft_printf("\n");
	}
	ft_printf("\n");

}

void	ft_printmatrix2(double **mtrx)
{
	int i = -1;
	int j;

	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			ft_printf("%10.5f  ", mtrx[i][j]);
		ft_printf("\n");
	}
	ft_printf("\n");
}

int ft_deal_key(int key, t_map *map)
{
	mlx_clear_window(g_mlx_ptr, g_window_ptr);
	key == 53 ? ft_exit(NULL, 0) : 0;
	key == 125 ? map->params->anglex += 10 : 0;
	key == 126 ? map->params->anglex -= 10 : 0;
	key == 69 ? map->params->scale *= 1.5 : 0;
	key == 78 ? map->params->scale /= 1.5 : 0;
	key == 1 ? map->params->yshift += 20 : 0;
	key == 13 ? map->params->yshift -= 20 : 0;
	key == 0 ? map->params->xshift -= 20 : 0;
	key == 2 ? map->params->xshift += 20 : 0;
	ft_calc_coord(map);
	ft_draw_map(map);
	return (0);
}
int ft_deal_mouse(int key,int x, int y, t_map *map)
{
	x = y;
	mlx_clear_window(g_mlx_ptr, g_window_ptr);
	key == 4 ? map->params->anglex += 10 : 0;
	key == 5 ? map->params->anglex -= 10 : 0;
	key == 7 ? map->params->angley += 10 : 0;
	key == 6 ? map->params->angley -= 10 : 0;
	ft_calc_coord(map);
	ft_draw_map(map);
	return (0);
}
int		main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		ft_exit("Usage : fdf [map].", 32);
	map = ft_parser(av[1]);
	map->params = (t_params *)ft_memalloc(sizeof(t_params));
	map->params->scale = 1;
	g_mlx_ptr = mlx_init();
	g_window_ptr = mlx_new_window(g_mlx_ptr, 1500, 1000, "FDF");
	ft_calc_coord(map);
	ft_draw_map(map);
	mlx_mouse_hook(g_window_ptr, ft_deal_mouse, map);
	mlx_key_hook(g_window_ptr, ft_deal_key, map);
	mlx_hook(g_window_ptr, 17, 0, ft_exit, NULL);
//	ft_printmatrix(g_map->basematrix);
//ft_printf("HEX = %d\n", ft_atoi_hex("10f"));
	system("leaks -q fdf");
	mlx_loop(g_mlx_ptr);
	return 0;
}
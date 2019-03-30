/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:05:45 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 17:05:45 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	(mtrx = (double **)ft_memalloc(sizeof(double *) * 3)) ?
	0 : ft_exit(strerror(errno), errno);
	while (++i < 3)
	{
		(mtrx[i] = (double *)ft_memalloc(sizeof(double) * 3)) ?
		0 : ft_exit(strerror(errno), errno);
	}
	ft_init_rotmtrx(mtrx, angle, c);
	return (mtrx);
}

void	ft_calc_mtrx(t_map *map)
{
	double	**scaler;
	int		i;

	i = -1;
	(scaler = (double **)ft_memalloc(sizeof(double *) * 3)) ?
	0 : ft_exit(strerror(errno), errno);
	while (++i < 3)
	{
		(scaler[i] = (double *)ft_memalloc(sizeof(double) * 3)) ?
		0 : ft_exit(strerror(errno), errno);
		scaler[i][i] = map->params->scale;
	}
	ft_multiple_mtrx(ft_rotmx(map->params->anglex, 'x'), map);
	ft_multiple_mtrx(ft_rotmx(map->params->angley, 'y'), map);
	ft_multiple_mtrx(ft_rotmx(map->params->anglez, 'z'), map);
	ft_multiple_mtrx(scaler, map);
}

void	ft_calc_coord(t_map *map)
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
			(map->xvalue)[i][j] = (map->basematrix[0][0] * (j - map->sizex / 2)
			+ map->basematrix[0][1] * (i - map->sizey / 2)
			+ map->basematrix[0][2] * map->altitude[i][j]);
			(map->xvalue)[i][j] += map->params->xshift;
			(map->yvalue)[i][j] = (map->basematrix[1][0] * (j - map->sizex / 2)
			+ map->basematrix[1][1] * (i - map->sizey / 2)
			+ map->basematrix[1][2] * map->altitude[i][j]);
			(map->yvalue)[i][j] += map->params->yshift;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:05:05 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 17:05:06 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_atoi_hex(const char *str)
{
	unsigned long long	nbr;
	int					tmp;

	nbr = 0;
	tmp = 0;
	while (*str && ft_strchr("0123456789ABCDEFabcdef", *str))
	{
		tmp = ft_strchr("0123456789", *str) ? *str - '0' : tmp;
		tmp = ft_strchr("ABCDEF", *str) ? *str - 55 : tmp;
		tmp = ft_strchr("abcdef", *str) ? *str - 87 : tmp;
		nbr = nbr * 16 + tmp;
		str++;
	}
	return ((int)nbr);
}

void	ft_copymtrx(double mtrx[3][3], t_map *map)
{
	int	i;
	int	j;

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

void	ft_reset_base_matrix(t_map *map)
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

void	ft_delmtrx(double **mtrx)
{
	free(mtrx[2]);
	free(mtrx[1]);
	free(mtrx[0]);
	free(mtrx);
}

void	ft_multiple_mtrx(double **mtrx, t_map *map)
{
	double	tmp[3][3];
	int		i;
	int		j;

	ft_copymtrx(tmp, map);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			map->basematrix[i][j] = tmp[i][0] * mtrx[0][j]
				+ tmp[i][1] * mtrx[1][j] + tmp[i][2] * mtrx[2][j];
		}
	}
	ft_delmtrx(mtrx);
}

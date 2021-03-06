/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:54:51 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 16:54:51 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_exit(char *stre, int errn)
{
	if (stre)
		ft_printf("Error : %s\n", stre);
	system("leaks -q fdf");
	exit(errn);
}

int		main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		ft_exit("Usage : fdf [map].", 32);
	map = ft_parser(av[1]);
	(map->params = (t_params *)ft_memalloc(sizeof(t_params))) ?
	0 : ft_exit(strerror(errno), errno);
	(map->mlx_ptr = mlx_init()) ? 0 : ft_exit("mlx_init.", 45);
	(map->window_ptr = mlx_new_window(map->mlx_ptr, 1500, 1000, "FDF")) ?
	0 : ft_exit("mlx_new_window.", 46);
	ft_reset(map);
	mlx_hook(map->window_ptr, 4, 0, ft_deal_mouse, map);
	mlx_hook(map->window_ptr, 2, 0, ft_deal_key, map);
	mlx_hook(map->window_ptr, 17, 0, ft_exit, NULL);
	system("leaks -q fdf");
	mlx_loop(map->mlx_ptr);
	return (0);
}

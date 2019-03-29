/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:43:16 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 17:43:16 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_menu(t_map *map)
{
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 50, 0xffffff, "Scroll - rotate");
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 70, 0xffffff, "I - isometric");
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 90, 0xffffff, "F - frontal");
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 110, 0xffffff, "+ , - scale");
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 130, 0xffffff, "A S D W - shift image");
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 150, 0xffffff, "R - reset");
	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 170, 0xffffff, "M - hide MENU");
//	mlx_string_put(map->mlx_ptr, map->window_ptr, 50, 190, 0xffffff, "MENU");
}

int		ft_deal_key(int key, t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->window_ptr);
	key == 53 ? ft_exit(NULL, 0) : 0;
	key == 69 ? map->params->scale *= 1.5 : 0;
	key == 78 ? map->params->scale /= 1.5 : 0;
	key == 1 ? map->params->yshift += 20 : 0;
	key == 13 ? map->params->yshift -= 20 : 0;
	key == 0 ? map->params->xshift -= 20 : 0;
	key == 2 ? map->params->xshift += 20 : 0;
	key == 15 ? ft_reset(map) : 0;
	key == 34 ? ft_iso(map) : 0;
	key == 3 ? ft_front(map) : 0;
	key == 46 ? map->menu = !map->menu : 0;
	ft_draw_map(map);
	map->menu ? ft_menu(map) : mlx_string_put(map->mlx_ptr,
			map->window_ptr, 50, 50, 0xffffff, "Press M");
	return (0);
}

int		ft_deal_mouse(int key, int x, int y, t_map *map)
{
	x = y;
	mlx_clear_window(map->mlx_ptr, map->window_ptr);
	key == 4 ? map->params->anglex += 10 : 0;
	key == 5 ? map->params->anglex -= 10 : 0;
	key == 7 ? map->params->angley += 10 : 0;
	key == 6 ? map->params->angley -= 10 : 0;
	ft_draw_map(map);
	map->menu ? ft_menu(map) : mlx_string_put(map->mlx_ptr,
			map->window_ptr, 50, 50, 0xffffff, "Press M");
	return (0);
}

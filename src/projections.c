/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:45:26 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 17:45:26 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_iso(t_map *map)
{
	map->params->xshift = 750;
	map->params->yshift = 500;
	map->params->anglex = 30;
	map->params->angley = 0;
	map->params->anglez = 30;
	ft_draw_map(map);
}

void	ft_reset(t_map *map)
{
	map->params->scale = 1;
	map->params->xshift = 750;
	map->params->yshift = 500;
	map->params->anglex = 0;
	map->params->angley = 0;
	map->params->anglez = 0;
	map->menu = 1;
	ft_draw_map(map);
	ft_menu(map);
}

void	ft_front(t_map *map)
{
	map->params->xshift = 750;
	map->params->yshift = 500;
	map->params->anglex = 90;
	map->params->angley = 0;
	map->params->anglez = 0;
	ft_draw_map(map);
}

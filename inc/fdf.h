/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:40:13 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 17:40:14 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define FDF_PTR map->mlx_ptr, map->window_ptr
# define MPR ft_exit(strerror(errno), errno)
# define MAL ft_memalloc
# include "libft.h"
# include <mlx.h>
# include <limits.h>
# include <math.h>
# include <errno.h>

typedef struct	s_map
{
	double			basematrix[3][3];
	int				sizex;
	int				sizey;
	double			**xvalue;
	double			**yvalue;
	int				**altitude;
	int				**color;
	struct s_params	*params;
	void			*mlx_ptr;
	void			*window_ptr;
	int				menu;
}				t_map;

typedef struct	s_input
{
	char			**line;
	char			**altitude;
	char			**color;
	int				len;
	struct s_input	*next;
}				t_input;

typedef struct	s_params
{
	int		anglex;
	int		angley;
	int		anglez;
	int		xshift;
	int		yshift;
	double	scale;
}				t_params;

typedef struct	s_coord
{
	int x1;
	int yy1;
	int x2;
	int y2;
	int color1;
	int	color2;
	int dx;
	int	dy;
}				t_coord;

t_map			*ft_parser(char *fname);
void			ft_draw_map(t_map *map);
void			ft_calc_coord(t_map *map);
void			ft_bresenham(t_coord c, t_map *map);
void			ft_delmtrx(double **mtrx);
int				ft_exit(char *stre, int errn);
int				ft_deal_key(int key, t_map *map);
int				ft_deal_mouse(int key, int x, int y, t_map *map);
int				ft_atoi_hex(const char *str);
void			ft_reset_base_matrix(t_map *map);
void			ft_multiple_mtrx(double **mtrx, t_map *map);
void			ft_reset(t_map *map);
void			ft_iso(t_map *map);
void			ft_front(t_map *map);
void			ft_menu(t_map *map);

#endif

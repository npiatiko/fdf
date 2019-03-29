#ifndef FDF_H
#define FDF_H

#include "./libft/includes/libft.h"
#include <mlx.h>
# include <limits.h>
# include <math.h>

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
}				t_map;

typedef struct	s_input
{
	char			**line;
	char 			**altitude;
	char 			**color;
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
}				t_coord;
void		*g_mlx_ptr;
void		*g_window_ptr;

t_map * ft_parser(char *fname);
void ft_draw_map(t_map *map);
void ft_calc_coord(t_map *map);
void drawLine(t_coord c);
void	ft_delmtrx(double **mtrx);
void	ft_printmatrix(double mtrx[3][3]);
void	ft_printmatrix2(double **mtrx);
int		ft_exit(char *stre, int errno);
int		ft_deal_key(int key, t_map *map);
int		ft_deal_mouse(int key,int x, int y, t_map *map);
int		ft_atoi_hex(const char *str);
#endif

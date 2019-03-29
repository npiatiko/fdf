/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:59:16 by npiatiko          #+#    #+#             */
/*   Updated: 2019/03/29 16:59:17 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_verify(char **data)
{
	int i;

	i = 0;
	ft_strchr("+-0123456789", data[0][0]) ? 0 :
	ft_exit("bad value of altitude.", 20);
	while (data[0][++i])
	{
		ft_strchr("0123456789", data[0][i]) ? 0 :
		ft_exit("bad value of altitude.", 20);
	}
	i = 1;
	if (data[1])
	{
		ft_strncmp(data[1], "0x", 2) ? ft_exit("bad value of color.", 25) : 0;
		ft_strlen(data[1] + 2) > 6 ? ft_exit("bad value of color.", 25) : 0;
		while (data[1][++i])
			ft_strchr("0123456789ABCDEFabcdef", data[1][i]) ? 0 :
			ft_exit("bad value of color.", 20);
	}
	return (data);
}

t_input	*ft_newinput(char *line)
{
	t_input	*new;
	int		i;
	char	**tmp;

	i = -1;
	new = (t_input *)ft_memalloc(sizeof(t_input));
	new->line = ft_strsplit(line, ' ');
	while ((new->line)[new->len])
	{
		if (!ft_strchr("+-0123456789", (new->line)[new->len][0]))
			ft_exit("bad value of altitude.", 20);
		new->len++;
	}
	new->altitude = (char **)ft_memalloc(sizeof(char *) * new->len);
	new->color = (char **)ft_memalloc(sizeof(char *) * new->len);
	while (++i < new->len)
	{
		tmp = ft_verify(ft_strsplit((new->line)[i], ','));
		new->altitude[i] = tmp[0];
		new->color[i] = tmp[1] ? tmp[1] : ft_strdup("0xffffff");
		free(tmp);
	}
	return (new);
}

void	ft_input_pushback(t_input **head, t_input *new)
{
	t_input	*tmp;

	tmp = *head;
	if (!*head)
		*head = new;
	else
	{
		if (new->len != (*head)->len)
			ft_exit("invalid format file. Different lengths of lines.", 10);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_coord(t_map *map, t_input *input)
{
	int i;
	int	j;

	i = -1;
	map->altitude = (int **)ft_memalloc(sizeof(int *) * map->sizey);
	map->color = (int **)ft_memalloc(sizeof(int *) * map->sizey);
	map->xvalue = (double **)ft_memalloc(sizeof(double *) * map->sizey);
	map->yvalue = (double **)ft_memalloc(sizeof(double *) * map->sizey);
	while (++i < map->sizey)
	{
		j = -1;
		map->altitude[i] = (int *)ft_memalloc(sizeof(int) * map->sizex);
		map->color[i] = (int *)ft_memalloc(sizeof(int) * map->sizex);
		(map->xvalue)[i] = (double *)ft_memalloc(sizeof(double) * map->sizex);
		(map->yvalue)[i] = (double *)ft_memalloc(sizeof(double) * map->sizex);
		while (++j < map->sizex)
		{
			map->color[i][j] = ft_atoi_hex((input->color)[j] + 2);
			map->altitude[i][j] = ft_atoi((input->altitude)[j]);
		}
		input = input->next;
	}
}

t_map	*ft_parser(char *fname)
{
	int				fd;
	char			*line;
	t_map			*map;
	static t_input	*input = NULL;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->sizex = -1;
	if ((fd = open(fname, O_RDONLY)) <= 0)
		ft_exit("bad filename.", 20);
	read(fd, NULL, 0) < 0 ? ft_exit("is dir.", 21) : 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_input_pushback(&input, ft_newinput(line));
		map->sizey++;
		map->sizex = map->sizex == -1 ? input->len : map->sizex;
		free(line);
	}
	close(fd);
	ft_coord(map, input);
	return (map);
}

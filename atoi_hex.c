#include "fdf.h"

int		ft_atoi_hex(const char *str)
{
	unsigned long long	nbr;
	int 				tmp;

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

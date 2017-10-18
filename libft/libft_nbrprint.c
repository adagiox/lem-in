/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_nbrprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 02:16:25 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 02:16:27 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

const char	g_hex[] = {'a', 'b', 'c', 'd', 'e', 'f',
	'A', 'B', 'C', 'D', 'E', 'F'};

void	ft_itoa_base(t_printf *flags, unsigned long long int value, int base,
	int offset)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = ft_getdigits(value, base);
	str = (char *)malloc(sizeof(char) * size + 1);
	i = size;
	str[i] = '\0';
	i--;
	while (value)
	{
		if (value % base > 9)
			str[i] = g_hex[value % base - 10 + offset];
		else
			str[i] = value % base + 48;
		value /= base;
		i--;
	}
	ft_pfputstr(flags, str);
	free(str);
}

void	ft_uputnbr(t_printf *flags, unsigned long long int i)
{
	if (i == 0)
	{
		ft_pfputchar(flags, '0');
		return ;
	}
	if (i / 10)
		ft_uputnbr(flags, i / 10);
	ft_pfputchar(flags, i % 10 + '0');
}

void	ft_pfputnbr(t_printf *flags, long long int i)
{
	if (i < 0)
	{
		if (i < -9223372036854775807)
		{
			ft_pfputnbr(flags, i / 10);
			ft_pfputchar(flags, '8');
			return ;
		}
		ft_pfputchar(flags, '-');
		i = -i;
	}
	if (i / 10)
		ft_pfputnbr(flags, i / 10);
	ft_pfputchar(flags, i % 10 + '0');
}

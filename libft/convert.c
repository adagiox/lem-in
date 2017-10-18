/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:31:31 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:31:36 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	convert_u(t_printf *flags, va_list args)
{
	unsigned long long int u;

	if (flags->spec == 'p')
		flags->alt = 1;
	if (flags->prec_set)
		flags->pad = 0;
	if (flags->showsign)
		flags->showsign = 0;
	if (flags->space == 1)
		flags->space = 0;
	u = va_arg(args, unsigned long long int);
	cast_uint(flags, u);
	return (1);
}

int	convert_i(t_printf *flags, va_list args)
{
	long long int i;

	if (flags->prec_set)
		flags->pad = 0;
	i = va_arg(args, long long int);
	cast_int(flags, i);
	return (1);
}

int	convert_s(t_printf *flags, va_list args)
{
	char *s;

	if (flags->is_long == 1)
		convert_ws(flags, args);
	else
	{
		if ((s = va_arg(args, char *)) == NULL)
		{
			ft_pfputstr(flags, "(null)");
			return (1);
		}
		print_s(flags, s);
	}
	return (1);
}

int	convert_ws(t_printf *flags, va_list args)
{
	wchar_t *ws;

	if ((ws = va_arg(args, wchar_t *)) == NULL)
	{
		ft_pfputstr(flags, "(null)");
		return (1);
	}
	print_ws(flags, ws);
	return (1);
}

int	convert_c(t_printf *flags, va_list args)
{
	int c;

	if (flags->is_long == 1)
		convert_wc(flags, args);
	else
	{
		c = va_arg(args, int);
		print_c(flags, c);
	}
	return (1);
}

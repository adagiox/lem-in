/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:33:50 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:33:53 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	print_s(t_printf *flags, char *s)
{
	int num_char;

	num_char = ft_strlen(s);
	if (flags->prec < num_char && flags->prec_set == 1)
		num_char = flags->prec;
	else if (flags->prec > num_char && flags->prec_set == 1)
		flags->prec = num_char;
	if (num_char < flags->width)
		flags->width = flags->width - num_char;
	if (flags->left == 1)
	{
		ft_putnstr(flags, s, num_char);
		print_space(flags, flags->width);
	}
	else
	{
		print_space(flags, flags->width);
		ft_putnstr(flags, s, num_char);
	}
	return (1);
}

int	print_ws(t_printf *flags, wchar_t *ws)
{
	int num_char;

	num_char = ft_wstrlen(ws);
	if (flags->prec < num_char && flags->prec_set == 1)
		num_char = flags->prec;
	else if (flags->prec > num_char && flags->prec_set == 1)
		flags->prec = num_char;
	if (num_char < flags->width)
		flags->width = flags->width - num_char;
	if (flags->left == 1)
	{
		ft_wputnstr(flags, ws, num_char);
		print_space(flags, flags->width);
	}
	else
	{
		print_space(flags, flags->width);
		ft_wputnstr(flags, ws, num_char);
	}
	return (1);
}

int	print_c(t_printf *flags, int c)
{
	if (flags->width > 1)
	{
		flags->width = flags->width - 1;
		if (flags->left == 1)
		{
			ft_pfputchar(flags, c);
			print_space(flags, flags->width);
		}
		else
		{
			print_space(flags, flags->width);
			ft_pfputchar(flags, c);
		}
	}
	else
		ft_pfputchar(flags, c);
	return (1);
}

int	print_wc(t_printf *flags, wchar_t wc)
{
	if (flags->width > 1)
	{
		flags->width = flags->width - 1;
		if (flags->left == 1)
		{
			ft_wputchar(flags, wc);
			print_space(flags, flags->width);
		}
		else
		{
			print_space(flags, flags->width);
			ft_wputchar(flags, wc);
		}
	}
	else
		ft_wputchar(flags, wc);
	return (1);
}

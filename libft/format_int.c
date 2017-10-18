/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:32:11 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:32:13 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		zero_case_int(t_printf *flags, long long int i)
{
	if (i == 0)
	{
		if (flags->prec == 0 && flags->width == 0)
			return (1);
		else if (flags->prec == 0 && flags->width > 0)
		{
			print_space(flags, flags->width);
			return (1);
		}
	}
	return (0);
}

void	print_left_int(t_printf *flags, int num_space, int num_zero,
	long long int i)
{
	print_prefix(flags);
	print_zero(flags, num_zero);
	ft_pfputnbr(flags, i);
	print_space(flags, num_space);
}

void	print_int(t_printf *flags, int num_space, int num_zero, long long int i)
{
	if (flags->pad)
	{
		if (i < 0)
		{
			ft_pfputchar(flags, '-');
			i = -i;
		}
		print_prefix(flags);
		print_zero(flags, num_space);
	}
	else
	{
		print_space(flags, num_space);
		if (i < 0)
		{
			ft_pfputchar(flags, '-');
			i = -i;
		}
		print_prefix(flags);
	}
	print_zero(flags, num_zero);
	ft_pfputnbr(flags, i);
}

int		format_int(t_printf *flags, long long int i)
{
	int num_space;
	int num_digits;
	int num_zero;

	num_space = 0;
	num_zero = 0;
	if (set_prefix(flags, i) && zero_case_int(flags, i) == 1)
		return (1);
	if ((num_digits = ft_countdigits(i)) < flags->prec)
	{
		num_zero = flags->prec - num_digits;
		num_digits = flags->prec;
	}
	if (flags->prefix == '-' || flags->prefix == '+' || flags->prefix == ' ')
		num_digits++;
	if (num_digits <= flags->width)
		num_space = flags->width - num_digits;
	if (flags->left)
		print_left_int(flags, num_space, num_zero, i);
	else
		print_int(flags, num_space, num_zero, i);
	return (1);
}

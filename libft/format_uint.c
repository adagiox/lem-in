/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:32:37 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:32:38 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void	print_left_uint(t_printf *flags, int num_space, int num_zero,
	unsigned long long int i)
{
	print_prefix(flags);
	print_zero(flags, num_zero);
	ft_uputnbr(flags, i);
	print_space(flags, num_space);
}

void	print_uint(t_printf *flags, int num_space, int num_zero,
	unsigned long long int i)
{
	if (flags->pad)
	{
		print_prefix(flags);
		print_zero(flags, num_space);
	}
	else
	{
		print_space(flags, num_space);
		print_prefix(flags);
	}
	print_zero(flags, num_zero);
	ft_uputnbr(flags, i);
}

int		format_uint(t_printf *flags, unsigned long long int i)
{
	int num_space;
	int num_digits;
	int num_zero;

	num_space = 0;
	num_zero = 0;
	set_uprefix(flags);
	if ((num_digits = ft_ucountdigits(i)) < flags->prec)
	{
		num_zero = flags->prec - num_digits;
		num_digits = flags->prec;
	}
	if (flags->prefix == '+' || flags->prefix == ' ')
		num_digits++;
	if (num_digits <= flags->width)
		num_space = flags->width - num_digits;
	if (flags->left)
		print_left_uint(flags, num_space, num_zero, i);
	else
		print_uint(flags, num_space, num_zero, i);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_oct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:32:25 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:32:28 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		zero_case_oct(t_printf *flags, unsigned long long int i)
{
	if (i == 0)
	{
		if (flags->prec != 0 || flags->alt)
			ft_pfputchar(flags, '0');
		if (flags->prec == 0 && flags->width == 0)
			return (1);
		else if (flags->prec == 0 && flags->width > 0)
		{
			print_space(flags, flags->width);
			return (1);
		}
		return (1);
	}
	return (0);
}

void	print_left_oct(t_printf *flags, int num_space, int num_zero,
	unsigned long long int i)
{
	if (flags->alt && i != 0)
		ft_pfputchar(flags, '0');
	print_zero(flags, num_zero);
	ft_itoa_base(flags, i, 8, 0);
	print_space(flags, num_space);
}

void	print_oct(t_printf *flags, int num_space, int num_zero,
	unsigned long long int i)
{
	if (flags->pad)
	{
		if (flags->alt && i != 0)
			ft_pfputchar(flags, '0');
		print_zero(flags, num_space);
	}
	else
	{
		print_space(flags, num_space);
		if (flags->alt && i != 0)
			ft_pfputchar(flags, '0');
	}
	print_zero(flags, num_zero);
	ft_itoa_base(flags, i, 8, 0);
}

int		format_oct(t_printf *flags, unsigned long long int i)
{
	int num_space;
	int num_digits;
	int num_zero;

	num_space = 0;
	num_zero = 0;
	if (zero_case_oct(flags, i) == 1)
		return (1);
	if ((num_digits = ft_getdigits(i, 8)) < flags->prec)
	{
		num_zero = flags->prec - num_digits;
		num_digits = flags->prec;
	}
	if (flags->alt)
		num_digits++;
	if (num_digits <= flags->width)
		num_space = flags->width - num_digits;
	if (flags->left)
		print_left_oct(flags, num_space, num_zero, i);
	else
		print_oct(flags, num_space, num_zero, i);
	return (1);
}

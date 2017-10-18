/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:32:01 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:32:03 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		zero_case_hex(t_printf *flags, unsigned long long int i)
{
	set_uprefix(flags);
	if (i == 0)
	{
		if (flags->prec == 0 && flags->width == 0)
			return (1);
		else if (flags->prec == 0 && flags->width > 0)
		{
			print_space(flags, flags->width);
			return (1);
		}
		if (flags->spec == 'p')
			ft_pfputstr(flags, "0x");
		if (flags->prec != 0)
			ft_pfputchar(flags, '0');
		return (1);
	}
	return (0);
}

int		get_offset(t_printf *flags)
{
	int offset;

	offset = 0;
	if (flags->spec == 'X')
		offset = 6;
	return (offset);
}

void	print_left_hex(t_printf *flags, int num_space, int num_zero,
	unsigned long long int i)
{
	if (flags->alt)
	{
		ft_pfputchar(flags, '0');
		print_prefix(flags);
	}
	print_zero(flags, num_zero);
	ft_itoa_base(flags, i, 16, get_offset(flags));
	print_space(flags, num_space);
}

void	print_hex(t_printf *flags, int num_space, int num_zero,
	unsigned long long int i)
{
	if (flags->pad)
	{
		if (flags->alt)
		{
			ft_pfputchar(flags, '0');
			print_prefix(flags);
		}
		print_zero(flags, num_space);
	}
	else
	{
		print_space(flags, num_space);
		if (flags->alt)
		{
			ft_pfputchar(flags, '0');
			print_prefix(flags);
		}
	}
	print_zero(flags, num_zero);
	ft_itoa_base(flags, i, 16, get_offset(flags));
}

int		format_hex(t_printf *flags, unsigned long long int i)
{
	int num_space;
	int num_digits;
	int num_zero;

	num_space = 0;
	num_zero = 0;
	if (zero_case_hex(flags, i) == 1)
		return (1);
	if ((num_digits = ft_getdigits(i, 16)) < flags->prec)
	{
		num_zero = flags->prec - num_digits;
		num_digits = flags->prec;
	}
	if (flags->alt)
		num_digits += 2;
	if (num_digits <= flags->width)
		num_space = flags->width - num_digits;
	if (flags->left)
		print_left_hex(flags, num_space, num_zero, i);
	else
		print_hex(flags, num_space, num_zero, i);
	return (1);
}

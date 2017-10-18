/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:33:38 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:33:40 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	print_space(t_printf *flags, int n)
{
	while (n)
	{
		ft_pfputchar(flags, ' ');
		n--;
	}
	return (1);
}

int	print_zero(t_printf *flags, int n)
{
	while (n)
	{
		ft_pfputchar(flags, '0');
		n--;
	}
	return (1);
}

int	print_prefix(t_printf *flags)
{
	if (flags->prefix == '+' || flags->prefix == ' ' || flags->prefix == 'x' ||
		flags->prefix == 'X')
		ft_pfputchar(flags, flags->prefix);
	return (1);
}

int	set_prefix(t_printf *flags, long long int i)
{
	if (i < 0)
		flags->prefix = '-';
	else if (i >= 0 && flags->showsign)
		flags->prefix = '+';
	else if (flags->space)
		flags->prefix = ' ';
	return (1);
}

int	set_uprefix(t_printf *flags)
{
	if (flags->spec == 'O' || flags->spec == 'o')
		flags->prefix = '0';
	else if (flags->spec == 'x' || flags->spec == 'p')
		flags->prefix = 'x';
	else if (flags->spec == 'X')
		flags->prefix = 'X';
	else if (flags->showsign)
		flags->prefix = '+';
	else if (flags->space)
		flags->prefix = ' ';
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:31:17 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:31:19 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	cast_int(t_printf *flags, long long int i)
{
	if (flags->is_int)
		i = (int)i;
	else if (flags->is_short)
		i = (short)i;
	else if (flags->is_char)
		i = (char)i;
	if (flags->prec_set || flags->showsign || flags->left || flags->space ||
		flags->width > 0)
		format_int(flags, i);
	else
		ft_pfputnbr(flags, i);
	return (1);
}

int	cast_uint(t_printf *flags, unsigned long long i)
{
	if (flags->is_int)
		i = (unsigned int)i;
	else if (flags->is_short)
		i = (unsigned short)i;
	else if (flags->is_char)
		i = (unsigned char)i;
	if (flags->spec == 'o' || flags->spec == 'O')
		format_oct(flags, i);
	else if (flags->spec == 'x' || flags->spec == 'X' || flags->spec == 'p')
		format_hex(flags, i);
	else if (flags->prec_set || flags->showsign || flags->left || flags->space
		|| flags->width > 0)
		format_uint(flags, i);
	else
		ft_uputnbr(flags, i);
	return (1);
}

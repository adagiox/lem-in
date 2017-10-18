/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_wc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:31:46 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:31:48 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	convert_wc(t_printf *flags, va_list args)
{
	wchar_t wc;

	wc = va_arg(args, wchar_t);
	return (print_wc(flags, wc));
}

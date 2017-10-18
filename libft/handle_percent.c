/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:33:13 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:33:15 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	handle_percent(t_printf *flags)
{
	int num_char;

	num_char = 1;
	if (num_char <= flags->width)
		flags->width = flags->width - num_char;
	if (flags->left == 1)
	{
		ft_pfputchar(flags, '%');
		print_space(flags, flags->width);
	}
	else
	{
		print_space(flags, flags->width);
		ft_pfputchar(flags, '%');
	}
	return (1);
}

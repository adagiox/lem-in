/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 02:14:37 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 02:14:39 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void	ft_pfputchar(t_printf *flags, int c)
{
	flags->length++;
	write(1, &c, 1);
}

void	ft_pfputstr(t_printf *flags, char *s)
{
	while (*s)
	{
		ft_pfputchar(flags, *s);
		s++;
	}
}

void	ft_putnstr(t_printf *flags, char *s, int n)
{
	while (*s && n)
	{
		ft_pfputchar(flags, *s);
		s++;
		n--;
	}
}

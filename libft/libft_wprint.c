/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_wprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 02:17:24 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 02:17:26 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void	ft_wputnstr(t_printf *flags, wchar_t *ws, int n)
{
	while (*ws && n)
	{
		ft_wputchar(flags, *ws);
		ws++;
		n--;
	}
}

int		ft_wputstr(t_printf *flags, wchar_t *ws)
{
	while (*ws)
	{
		ft_wputchar(flags, *ws);
		ws++;
	}
	return (1);
}

int		ft_wclen(wchar_t wc)
{
	if ((unsigned int)wc < 128)
		return (1);
	else if ((unsigned int)wc < 2048)
		return (2);
	else if ((unsigned int)wc < 65536)
		return (3);
	else
		return (4);
}

int		ft_wstrlen(wchar_t *ws)
{
	int len;

	len = 0;
	if (!ws)
		return (ft_strlen("(null)"));
	while (*ws)
	{
		len += ft_wclen(*ws);
		ws++;
	}
	return (len);
}

int		ft_wputchar(t_printf *flags, wchar_t wc)
{
	if ((unsigned int)wc < 128)
		ft_pfputchar(flags, (unsigned int)wc);
	else if ((unsigned int)wc < 2048)
	{
		ft_pfputchar(flags, ((unsigned int)wc >> 6) | 192);
		ft_pfputchar(flags, ((unsigned int)wc & 63) | 128);
		return (2);
	}
	else if ((unsigned int)wc < 65536)
	{
		ft_pfputchar(flags, ((unsigned int)wc >> 12) | 224);
		ft_pfputchar(flags, (((unsigned int)wc >> 6) & 63) | 128);
		ft_pfputchar(flags, (((unsigned int)wc) & 63) | 128);
		return (3);
	}
	else
	{
		ft_pfputchar(flags, ((unsigned int)wc >> 18) | 240);
		ft_pfputchar(flags, (((unsigned int)wc >> 12) & 63) | 128);
		ft_pfputchar(flags, (((unsigned int)wc >> 6) & 63) | 128);
		ft_pfputchar(flags, ((unsigned int)wc & 63) | 128);
		return (4);
	}
	return (1);
}

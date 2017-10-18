/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 02:20:27 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 02:20:29 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	ft_getdigits(unsigned long long int value, int base)
{
	int count;

	count = 0;
	while (value)
	{
		value /= base;
		count++;
	}
	return (count);
}

int	ft_countdigits(long long int i)
{
	int count;

	count = 0;
	if (i == 0)
		return (1);
	if (i < 0)
		i = -i;
	while (i)
	{
		i /= 10;
		count++;
	}
	return (count);
}

int	ft_ucountdigits(unsigned long long int i)
{
	int count;

	count = 0;
	if (i == 0)
		return (1);
	while (i)
	{
		i /= 10;
		count++;
	}
	return (count);
}

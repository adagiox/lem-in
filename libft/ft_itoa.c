/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 11:33:15 by erintala          #+#    #+#             */
/*   Updated: 2017/03/12 17:13:19 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static int	count_digits(int n)
{
	int				count;

	count = 1;
	while (n /= 10)
		count++;
	return (count);
}

char		*ft_itoa(int n)
{
	char			*nbr;
	unsigned int	i;
	int				size;

	size = count_digits(n);
	i = n < 0 ? -n : n;
	if (n < 0)
		size++;
	if (!(nbr = ft_strnew(size)))
		return (NULL);
	if (n == 0)
		return (ft_strdup("0"));
	nbr += size;
	*nbr = 0;
	while (i != 0)
	{
		*--nbr = i % 10 + '0';
		i /= 10;
	}
	if (n < 0)
		*--nbr = '-';
	return (nbr);
}

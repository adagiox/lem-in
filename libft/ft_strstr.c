/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 22:00:26 by erintala          #+#    #+#             */
/*   Updated: 2017/01/17 22:48:32 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;

	if (*little == 0)
		return ((char *)big);
	while (*big)
	{
		if (*little == *big)
		{
			i = 0;
			while (*little == *big && *little && *big)
			{
				i++;
				big++;
				little++;
			}
			if (*little == 0)
				return ((char *)big - i);
			little -= i;
			big -= i;
		}
		big++;
	}
	return (NULL);
}

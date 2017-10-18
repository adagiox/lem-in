/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:57:04 by erintala          #+#    #+#             */
/*   Updated: 2017/03/01 15:57:05 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	size_t	l;

	l = 0;
	if (*little == 0)
		return ((char *)big);
	while (*big && l < len)
	{
		if (*little == *big)
		{
			i = 0;
			while (*(little + i) == *(big + i) && *(little + i) && *(big + i)
				&& (l + i) < len)
				i++;
			if (*(little + i) == 0)
				return ((char *)big);
		}
		l++;
		big++;
	}
	return (NULL);
}

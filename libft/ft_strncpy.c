/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 13:37:35 by erintala          #+#    #+#             */
/*   Updated: 2017/01/17 23:06:23 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *d;

	d = dst;
	while (*src != '\0' && len > 0)
	{
		*d++ = *src++;
		len--;
	}
	while (len > 0)
	{
		*d++ = '\0';
		len--;
	}
	return (dst);
}

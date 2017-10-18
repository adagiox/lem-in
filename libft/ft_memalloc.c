/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:43:00 by erintala          #+#    #+#             */
/*   Updated: 2017/03/07 16:43:02 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char *alloc;

	if (size == 0)
		return (NULL);
	alloc = (unsigned char *)malloc(sizeof(char) * size);
	if (alloc == NULL)
		return (NULL);
	ft_bzero(alloc, size);
	return ((void *)alloc);
}

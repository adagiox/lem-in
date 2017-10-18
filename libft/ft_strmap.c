/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:03:19 by erintala          #+#    #+#             */
/*   Updated: 2017/03/10 15:03:20 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *str;
	char *i;

	if (s == NULL)
		return (NULL);
	str = ft_strnew(ft_strlen(s));
	i = str;
	if (str == NULL)
		return (NULL);
	while (*s)
	{
		*str = f(*s);
		str++;
		s++;
	}
	*str = 0;
	return (i);
}

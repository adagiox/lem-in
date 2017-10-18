/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 23:20:57 by erintala          #+#    #+#             */
/*   Updated: 2017/01/19 16:30:12 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char		*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((sizeof(char) * ft_strlen(s1)) + 1);
	if (str == NULL)
		return (NULL);
	while (*s1)
	{
		i++;
		*str++ = *s1++;
	}
	*str = '\0';
	return (str - i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:04:20 by erintala          #+#    #+#             */
/*   Updated: 2017/03/10 15:04:21 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char			*ret;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[j])
		j++;
	while (j > 0 && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t' ||
			s[j] == '\0'))
		j--;
	if (j == 0)
		return (ft_strnew(1));
	while (i < j && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	ret = (char *)malloc(sizeof(char) * (j - i) + 2);
	if (ret == NULL)
		return (NULL);
	ret = ft_strncpy(ret, &s[i], (j - i) + 1);
	ret[(j - i) + 1] = 0;
	return (ret);
}

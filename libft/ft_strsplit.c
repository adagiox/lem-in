/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:30:06 by erintala          #+#    #+#             */
/*   Updated: 2017/03/11 17:30:08 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static int	count_words(char *s, char c)
{
	int count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*make_next_word(char *s, char c)
{
	char	*word;
	int		size;

	size = 0;
	while (*s && *s != c)
	{
		size++;
		s++;
	}
	word = ft_strnew(size);
	if (word == NULL)
		return (NULL);
	s -= size;
	word = ft_strncpy(word, s, size);
	return (word);
}

static char	*get_next_word(char *s, int c)
{
	while (*s)
	{
		while (*s && *s != c)
			s++;
		while (*s == c)
			s++;
		if (*s && *s != c)
			return (s);
	}
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		size;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	size = count_words((char *)s, c);
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (split == NULL)
		return (NULL);
	if (*s == c)
		s = get_next_word((char *)s, c);
	while (size--)
	{
		split[i] = make_next_word((char *)s, c);
		if (split[i] == NULL)
			return (NULL);
		s = get_next_word((char *)s, c);
		i++;
	}
	split[i] = 0;
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:06:26 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:06:30 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	check_link_error(t_room_list *room_list, char *line)
{
	if (g_start == 0 || g_end == 0 || (ft_strstr(line, " ") && line[0] != '#')
		|| (add_link_line(room_list, line)) == 0)
	{
		ft_strdel(&line);
		return (-1);
	}
	return (1);
}

int	check_link_space(char *new_line)
{
	if (ft_strstr(new_line, " ") && new_line[0] != '#')
	{
		ft_strdel(&new_line);
		return (-1);
	}
	return (1);
}

int	check_hash(char *new_line)
{
	if (new_line[0] == '#')
	{
		ft_strdel(&new_line);
		return (1);
	}
	return (-1);
}

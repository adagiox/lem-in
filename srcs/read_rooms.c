/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:07:05 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:07:07 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room		*next_line_room(char *line)
{
	t_room	*room;
	char	**split;

	split = ft_strsplit(line, ' ');
	if (check_room_split(split) == -1)
		return (NULL);
	room = new_room(0, 0, split);
	free_split(split);
	free(split);
	return (room);
}

t_room_list	*read_rooms_read_links(t_room_list *room_list, char *line)
{
	if ((read_links(line, room_list)) == -1)
		return (NULL);
	ft_strdel(&line);
	return (room_list);
}

t_room_list	*read_rooms_command(t_room_list *room_list, char *line)
{
	if ((room_list = command(line, room_list)) == NULL)
	{
		ft_strdel(&line);
		return (NULL);
	}
	return (room_list);
}

t_room_list	*read_rooms_room_list(t_room_list *room_list, char *line)
{
	t_room *room_add;

	if (!ft_strstr(line, "-"))
	{
		if (check_l(line) == -1)
			return (NULL);
		room_add = next_line_room(line);
		if ((room_list = add_room_list(room_add, room_list)) == NULL)
		{
			ft_strdel(&line);
			return (NULL);
		}
	}
	return (room_list);
}

t_room_list	*read_rooms(void)
{
	char		*line;
	int			ret;
	t_room_list	*room_list;

	room_list = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
		{
			if ((room_list = read_rooms_command(room_list, line)) == NULL)
				return (NULL);
		}
		else if (check_hash(line) == 1)
			continue ;
		else if (!ft_strstr(line, "-"))
		{
			if ((room_list = read_rooms_room_list(room_list, line)) == NULL)
				return (NULL);
		}
		else
			return (read_rooms_read_links(room_list, line));
		ft_strdel(&line);
	}
	return (room_list);
}

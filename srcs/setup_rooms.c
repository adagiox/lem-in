/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:08:03 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:08:04 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room_list	*new_room_list(t_room *room)
{
	t_room_list *new;

	new = (t_room_list *)malloc(sizeof(t_room_list));
	new->room = room;
	new->next_room_list = NULL;
	new->next_room = NULL;
	return (new);
}

t_room_list	*add_room_list(t_room *room, t_room_list *room_list)
{
	t_room_list *head;

	if (room == NULL)
		return (NULL);
	if (room_list == NULL)
		return (new_room_list(room));
	head = room_list;
	while (room_list->next_room_list != NULL)
		room_list = room_list->next_room_list;
	room_list->next_room_list = new_room_list(room);
	return (head);
}

t_room_list	*command(char *line, t_room_list *room_list)
{
	unsigned int	start;
	unsigned int	end;
	t_room			*room;

	start = 0;
	end = 0;
	if (ft_strstr(line, "##start"))
	{
		g_start++;
		start = 1;
	}
	else if (ft_strstr(line, "##end"))
	{
		g_end++;
		end = 1;
	}
	if (g_end > 1 || g_start > 1)
		return (NULL);
	if ((room = next_room(start, end)) == NULL)
		return (NULL);
	room_list = add_room_list(room, room_list);
	return (room_list);
}

t_room		*new_room(unsigned int start, unsigned int end, char **room)
{
	t_room	*new;
	char	*name;

	name = ft_strdup(room[0]);
	new = (t_room *)malloc(sizeof(t_room));
	new->name = name;
	new->dist = 0;
	new->is_set = 0;
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->ant = NULL;
	new->head_room = NULL;
	new->is_occupied = 0;
	new->is_start = start;
	new->is_end = end;
	return (new);
}

t_room		*next_room(unsigned int start, unsigned int end)
{
	char	*line;
	char	**split;
	t_room	*room;
	int		ret;

	if ((ret = get_next_line(0, &line)) <= 0)
	{
		ft_strdel(&line);
		return (NULL);
	}
	ft_printf("%s\n", line);
	if (line[0] == '#' || ft_strstr(line, "-") || line[1] == '#' ||
		line[0] == 'L')
	{
		ft_strdel(&line);
		return (NULL);
	}
	split = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (check_room_split(split) == -1)
		return (NULL);
	room = new_room(start, end, split);
	free_split(split);
	free(split);
	return (room);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:07:28 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:07:31 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room		*get_link_room(t_room_list *room_list, char *name)
{
	while (room_list != NULL && (ft_strcmp(room_list->room->name, name)) != 0)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	if (room_list->room->head_room == NULL)
		room_list->room->head_room = room_list;
	return (room_list->room);
}

t_room_list	*get_room_list_head(t_room_list *room_list, char *name)
{
	if (room_list == NULL || name == NULL)
		return (NULL);
	while (room_list != NULL && (ft_strcmp(room_list->room->name, name)) != 0)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	return (room_list);
}

t_room_list	*get_room_list(t_room *room)
{
	if (room == NULL)
		return (NULL);
	return (room->head_room);
}

t_room_list	*get_end(t_room_list *room_list)
{
	while (room_list->room->is_end != 1 && room_list != NULL)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	room_list->room->is_set = 1;
	return (room_list);
}

t_room_list	*get_start(t_room_list *room_list)
{
	while (room_list->room->is_start != 1 && room_list != NULL)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	return (room_list);
}

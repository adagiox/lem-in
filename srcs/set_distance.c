/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:07:51 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:07:52 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_queue	*new_queue(t_room *room, int dist)
{
	t_queue *queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = room;
	queue->room->dist = dist + 1;
	queue->room->is_set = 1;
	queue->next_room = NULL;
	return (queue);
}

t_queue	*enqueue(t_queue *queue, t_room *room, t_room_list *current)
{
	t_queue	*head;

	head = queue;
	if (queue == NULL)
		return (new_queue(room, current->room->dist));
	while (queue->next_room != NULL)
		queue = queue->next_room;
	queue->next_room = new_queue(room, current->room->dist);
	return (head);
}

t_queue	*dequeue(t_queue *queue)
{
	t_queue *current;

	if (queue != NULL)
	{
		current = queue;
		queue = queue->next_room;
		free(current);
	}
	return (queue);
}

t_room	*get_min_dist(t_room_list *room_list)
{
	t_room		*go;
	t_room_list	*src;

	src = room_list;
	room_list = room_list->next_room;
	if (room_list == NULL)
		return (NULL);
	go = room_list->room;
	while (room_list)
	{
		if (room_list->room->dist < src->room->dist &&
			room_list->room->is_occupied == 0)
			go = room_list->room;
		room_list = room_list->next_room;
	}
	if (go->is_occupied == 0 && go->dist < src->room->dist)
		return (go);
	return (NULL);
}

int		set_distance(t_room_list *room_list)
{
	t_room_list	*head;
	t_room_list	*current;
	t_queue		*queue;

	queue = NULL;
	head = room_list;
	current = get_end(head);
	while (current)
	{
		if ((room_list = current->next_room) == NULL)
			return (-1);
		while (room_list)
		{
			if (room_list->room->is_set == 0)
				queue = enqueue(queue, room_list->room, current);
			room_list = room_list->next_room;
		}
		if (queue == NULL)
			return (1);
		current = get_room_list(queue->room);
		queue = dequeue(queue);
	}
	current = get_start(head);
	return (current->room->is_set == 0 ? -1 : 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:06:56 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:06:59 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room	*check_move(t_ant *ant)
{
	t_room_list	*check_links;
	t_room		*go;

	check_links = get_room_list(ant->current_room);
	go = get_min_dist(check_links);
	return (go);
}

int		next_move(t_ant **ant)
{
	t_room	*go;
	t_ant	*current;

	current = *ant;
	while (current)
	{
		if (current->has_moved == 0)
		{
			if ((go = check_move(current)) != NULL)
			{
				move_ant_room(ant, current, go);
				return (1);
			}
		}
		current = current->next_ant;
	}
	return (1);
}

int		move_ant_room(t_ant **ant, t_ant *current, t_room *dest)
{
	t_room *src;

	src = current->current_room;
	src->is_occupied = 0;
	if (dest->is_end == 1)
	{
		current->at_end = 1;
		current->has_moved = 1;
		ft_printf("L%i-%s ", current->number, dest->name);
		*ant = (*ant)->next_ant;
		free(current);
	}
	else
	{
		dest->is_occupied = 1;
		current->current_room = dest;
		current->has_moved = 1;
		ft_printf("L%i-%s ", current->number, dest->name);
	}
	return (1);
}

int		get_moves(int n, t_room_list *room_list)
{
	int moves;

	room_list = get_start(room_list);
	moves = room_list->room->dist * 5;
	if (room_list->room->dist == 1)
		moves = n;
	return (moves);
}

int		move_ants(t_ant **ant, t_room_list *room_list)
{
	int turns;
	int move;
	int moves;

	turns = get_size_ants(*ant);
	moves = get_moves(turns, room_list);
	while (turns > 0)
	{
		move = moves;
		reset_ants(*ant);
		while (move > 0)
		{
			next_move(ant);
			move--;
		}
		turns = get_size_ants(*ant);
		ft_printf("\n");
	}
	return (1);
}

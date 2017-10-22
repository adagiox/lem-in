/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:07:14 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:07:16 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	set_ants(t_ant *ant, t_room_list *room_list)
{
	room_list = get_start(room_list);
	while (ant)
	{
		ant->current_room = room_list->room;
		ant = ant->next_ant;
	}
	return (1);
}

int	get_size_ants(t_ant *ant)
{
	int size;

	size = 0;
	while (ant)
	{
		if (ant->at_end == 0)
			size++;
		ant = ant->next_ant;
	}
	return (size);
}

int	reset_ants(t_ant *ant)
{
	while (ant)
	{
		ant->has_moved = 0;
		ant = ant->next_ant;
	}
	return (1);
}

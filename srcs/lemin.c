/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:06:49 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 16:06:51 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	lemin(void)
{
	t_ant		*ants;
	t_room_list	*room_list;

	if ((ants = read_ants()) == NULL)
		return (-1);
	if ((room_list = read_rooms()) == NULL)
		return (-1);
	if ((set_distance(room_list)) == -1)
		return (-1);
	set_ants(ants, room_list);
	ft_printf("\n");
	move_ants(&ants, room_list);
	free_room_list(room_list);
	return (1);
}

int	main(void)
{
	int ret;

	g_start = 0;
	g_end = 0;
	if ((ret = lemin()) == -1)
	{
		ft_printf("ERROR\n");
		return (-1);
	}
	return (0);
}

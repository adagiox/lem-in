#include "../includes/lemin.h"

void free_rooms(t_room_list *temp)
{
	if (temp->room != NULL)
	{
		ft_strdel(&temp->room->name);
		free(temp->room);
	}
}

int free_room_list(t_room_list *room_list)
{
	t_room_list *head;
	t_room_list *current;
	t_room_list *temp;

	head = room_list;
	while (head)
	{
		temp = head;
		head = head->next_room_list;
		free_rooms(temp);
	}
	head = room_list;
	while (head)
	{
		current = head;
		head = head->next_room_list;
		while (current)
		{
			temp = current;
			current = current->next_room;
			free(temp);
		}
	}
	return (1);
}
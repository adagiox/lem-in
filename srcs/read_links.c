#include "../includes/lemin.h"

t_room_list *new_link_next_room(t_room *new_link_room)
{
	t_room_list *new_next_room;

	new_next_room = (t_room_list *)malloc(sizeof(t_room_list));
	new_next_room->room = new_link_room;
	new_next_room->next_room = NULL;
	new_next_room->next_room_list = NULL;
	return (new_next_room);
}

int add_link_room(t_room_list *room_list_head, t_room *new_link_room)
{
	while (room_list_head->next_room != NULL)
		room_list_head = room_list_head->next_room;
	room_list_head->next_room = new_link_next_room(new_link_room);
	return (1);
}

int add_link_line(t_room_list *room_list, char *line)
{
	char **split;
	t_room_list *head;
	t_room *room_add;

	split = ft_strsplit(line, '-');
	if ((head = get_room_list_head(room_list, split[0])) == NULL)
	{
		free_split(split);
		return (0);
	}
	room_add = get_link_room(room_list, split[1]);
	add_link_room(head, room_add);
	if ((head = get_room_list_head(room_list, split[1])) == NULL)
	{
		free_split(split);
		return (0);
	}
	room_add = get_link_room(room_list, split[0]);
	add_link_room(head, room_add);
	free_split(split);
	free(split);
	return (1);
}

int read_links_add_link_line(t_room_list *room_list, char *new_line)
{
	if ((add_link_line(room_list, new_line)) == 0)
	{
		ft_strdel(&new_line);
		return (-1);
	}
	return (1);
}

int read_links(char *line, t_room_list *room_list)
{
	char *new_line;
	int ret;

	if (check_link_error(room_list, line) == -1)
		return (-1);
	while ((ret = get_next_line(0, &new_line)) > 0)
	{
		ft_printf("%s\n", new_line);
		if (check_link_space(new_line) == -1)
			return (-1);
		if (check_hash(new_line) == 1)
			continue ;
		else if (ft_strstr(new_line, "-"))
		{
			if (read_links_add_link_line(room_list, new_line) == -1)
				return (-1);
			ft_strdel(&new_line);
		}
		else
		{
			ft_strdel(&new_line);
			return (-1);
		}
	}
	return (1);
}
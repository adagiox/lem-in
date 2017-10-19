#include "../includes/lem-in.h"

void print_ants(t_ant *ant)
{
	while (ant != NULL)
	{
		ft_printf("Ant: %i\t\tMoved: %u\n", ant->number, ant->has_moved);
		ant = ant->next_ant;
	}
}

void print_room_list(t_room_list *room_list)
{
	while (room_list != NULL)
	{
		ft_printf("\nRoom: %s\n------------------\nx:\t\t%i\ny:\t\t%i\nis_start:\t%u\nis_end:\t\t%u\n", 
			room_list->room->name, room_list->room->x, room_list->room->y, 
			room_list->room->is_start, room_list->room->is_end);
		room_list = room_list->next_room_list;
	}
}

t_ant *new_ants(int size)
{
	t_ant *ant;
	t_ant *new;
	t_ant *head;
	int number;

	number = 1;
	head = (t_ant *)malloc(sizeof(t_ant));
	head->number = number;
	head->has_moved = 0;
	head->next_ant = NULL;
	number++;
	ant = head;
	while (number < size + 1)
	{
		while (ant->next_ant != NULL)
			ant = ant->next_ant;
		new = (t_ant *)malloc(sizeof(t_ant));
		new->number = number;
		new->has_moved = 0;
		new->next_ant = NULL;
		ant->next_ant = new;
		number++;
	}
	return (head);
}

t_ant *read_ants()
{
	char *line;
	t_ant *ant;
	int size;
	int ret;

	while ((ret = get_next_line(0, &line)))
	{
		if (ret > 0)
		{
			if (line[0] == '#' && line[1] != '#')
				continue ;
			else
				break ;
		}
		else
			return (NULL);
	}
	size = ft_atoi(line);
	if (size <= 0)
		return (NULL);
	ft_printf("size: %i\n", size);
	ant = new_ants(size);
	return (ant);
}

t_room_list *new_room_list(t_room *room)
{
	t_room_list *new;

	new = (t_room_list *)malloc(sizeof(t_room_list));
	new->room = room;
	new->next_room_list = NULL;
	return (new);
}

t_room_list *add_room_list(t_room *room, t_room_list *room_list)
{
	t_room_list *head;

	head = room_list;
	if (room_list == NULL)
		return (new_room_list(room));
	while (room_list->next_room_list != NULL)
		room_list = room_list->next_room_list;
	room_list->next_room_list = new_room_list(room);
	return (head);
}

t_room_list *command(char *line, t_room_list *room_list)
{
	char *new_line;
	unsigned int start;
	unsigned int end;
	t_room *room;

	start = 0;
	end = 0;
	if (ft_strstr(line, "##start"))
		start = 1;
	else if (ft_strstr(line, "##end"))
		end = 1;
	room = next_room(start, end);
	room_list = add_room_list(room, room_list);
	return (room_list);
}

t_room *new_room(unsigned int start, unsigned int end, char **room)
{
	t_room *new;

	new = (t_room *)malloc(sizeof(t_room));
	new->name = room[0];
	new->dist = -1;
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->ant = NULL;
	new->is_occupied = 0;
	new->is_start = start;
	new->is_end = end;
	new->next_room = NULL;
	return (new);
}

t_room *next_room(unsigned int start, unsigned int end)
{
	char *line;
	t_room *room;
	int ret;

	if((ret = get_next_line(0, &line)) <= 0)
		return (NULL);
	room = new_room(start, end, ft_strsplit(line, ' '));
	return (room);
}

t_room *next_line_room(char *line)
{
	t_room *room;

	room = new_room(0, 0, ft_strsplit(line, ' '));
	return (room);
}

t_room_list *read_rooms()
{
	char *line;
	int ret;
	t_room_list *room_list;

	room_list = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
			room_list = command(line, room_list);
		else if (line[0] == '#')
			continue ;
		else if (ft_strstr(line, "-"))
		{
			//read_links(room_list);
			return (room_list);
		}
		else
			room_list = add_room_list(next_line_room(line), room_list);
	}
	return (room_list);
}

// int read_links(t_room_list *room_list)
// {

// 	return (1);
// }

int	lemin()
{
	char *line;
	int ret;
	t_ant *ants;
	t_room_list *room_list;

	if ((ants = read_ants()) == NULL)
		 return (-1);
	print_ants(ants);
	if ((room_list = read_rooms()) == NULL)
		return (-1);
	print_room_list(room_list);
	return (1);
}

int main(void)
{
	int ret;

	if ((ret = lemin()) == -1)
	{
		ft_printf("ERROR\n");
		return (-1);
	}
	return (0);
}
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
		ft_printf("Distance:\t%i\n", room_list->room->dist);
		ft_printf("Links:\t\t");
		print_links(room_list);
		room_list = room_list->next_room_list;
	}
}

void print_links(t_room_list *room_list)
{
	t_room_list *head;

	head = room_list->next_room;
	while (head != NULL)
	{
		if (head->next_room == NULL)
			ft_printf("%s", head->room->name);
		else
			ft_printf("%s, ", head->room->name);
		head = head->next_room;
	}
	ft_printf("\n");
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
	ant = new_ants(size);
	return (ant);
}

t_room_list *new_room_list(t_room *room)
{
	t_room_list *new;

	new = (t_room_list *)malloc(sizeof(t_room_list));
	new->room = room;
	new->next_room_list = NULL;
	new->next_room = NULL;
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
	if ((room = next_room(start, end)) == NULL)
		return (NULL);
	room_list = add_room_list(room, room_list);
	return (room_list);
}

t_room *new_room(unsigned int start, unsigned int end, char **room)
{
	t_room *new;

	new = (t_room *)malloc(sizeof(t_room));
	new->name = room[0];
	new->dist = -1;
	new->is_set = 0;
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->ant = NULL;
	new->is_occupied = 0;
	new->is_start = start;
	new->is_end = end;
	return (new);
}

t_room *next_room(unsigned int start, unsigned int end)
{
	char *line;
	t_room *room;
	int ret;

	if ((ret = get_next_line(0, &line)) <= 0)
		return (NULL);
	if (line[0] == '#')
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
		{
			if ((room_list = command(line, room_list)) == NULL)
				return (NULL);
		}
		else if (line[0] == '#')
			continue ;
		else if (ft_strstr(line, "-"))
		{
			if ((read_links(line, room_list)) == -1)
				return (NULL);
			return (room_list);
		}
		else
			room_list = add_room_list(next_line_room(line), room_list);
	}
	return (room_list);
}

t_room *get_link_room(t_room_list *room_list, char *name)
{
	while ((ft_strcmp(room_list->room->name, name)) != 0 && room_list != NULL)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	return (room_list->room);
}

t_room_list *get_room_list_head(t_room_list *room_list, char *name)
{
	while ((ft_strcmp(room_list->room->name, name)) != 0 && room_list != NULL)
	{
		room_list = room_list->next_room_list;
	}
	if (room_list == NULL)
		return (NULL);
	return (room_list);
}

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

	print_room_list(room_list);
	split = ft_strsplit(line, '-');
	head = get_room_list_head(room_list, split[0]);
	room_add = get_link_room(room_list, split[1]);
	add_link_room(head, room_add);
	head = get_room_list_head(room_list, split[1]);
	room_add = get_link_room(room_list, split[0]);
	add_link_room(head, room_add);
	return (1);
}

int read_links(char *line, t_room_list *room_list)
{
	char *new_line;
	int ret;

	add_link_line(room_list, line);
	while ((ret = get_next_line(0, &new_line)) > 0)
	{
		if (ft_strstr(new_line, "-") && ret > 0)
			add_link_line(room_list, new_line);
		else if (new_line[0] == '#' && ret > 0)
			continue ;
		else
			break ;
	}
	return (1);
}

t_room_list *get_end(t_room_list *room_list)
{
	while (room_list->room->is_end != 1 && room_list != NULL)
		room_list = room_list->next_room_list;
	return (room_list);
}

int set_distance(t_room_list *room_list, int dist)
{
	while (room_list != NULL)
	{
		if (room_list->room->is_set == 1)
		{
			room_list = room_list->next_room;
			continue ;
		}
		room_list->room->dist = dist;
		room_list->room->is_set = 1;
		set_distance(room_list->next_room, dist + 1);
	}
	return (1);
}

int	lemin()
{
	char *line;
	int ret;
	t_ant *ants;
	t_room_list *room_list;

	if ((ants = read_ants()) == NULL)
		return (-1);
	if ((room_list = read_rooms()) == NULL)
		return (-1);
	set_distance(get_end(room_list), 0);
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
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
	// MEMORY LEAK HERE
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
	free(line);
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

	if (room_list == NULL)
		return (new_room_list(room));
	head = room_list;
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
	char *name;

	name = ft_strdup(room[0]);
	new = (t_room *)malloc(sizeof(t_room));
	new->name = name;
	new->dist = 0;
	new->is_set = 0;
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->ant = NULL;
	new->is_occupied = 0;
	new->is_start = start;
	new->is_end = end;
	//MEMORY LEAK HERE
	return (new);
}

t_room *next_room(unsigned int start, unsigned int end)
{
	char *line;
	char **split;
	t_room *room;
	int ret;

	if ((ret = get_next_line(0, &line)) <= 0)
		return (NULL);
	if (line[0] == '#')
		return (NULL);
	split = ft_strsplit(line, ' ');
	room = new_room(start, end, split);
	free(line);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	return (room);
}

t_room *next_line_room(char *line)
{
	t_room *room;
	char **split;

	split = ft_strsplit(line, ' ');
	room = new_room(0, 0, split);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
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
			{
				free(line);
				return (NULL);
			}
		}
		else if (line[0] == '#')
			continue ;
		else if (ft_strstr(line, "-"))
		{
			if ((read_links(line, room_list)) == -1)
			{
				free(line);
				return (NULL);
			}
			free(line);
			return (room_list);
		}
		else
			room_list = add_room_list(next_line_room(line), room_list);
		free(line);
	}
	free(line);
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
	if (room_list == NULL || name == NULL)
		return (NULL);
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

	//print_room_list(room_list);
	split = ft_strsplit(line, '-');
	head = get_room_list_head(room_list, split[0]);
	room_add = get_link_room(room_list, split[1]);
	add_link_room(head, room_add);
	head = get_room_list_head(room_list, split[1]);
	room_add = get_link_room(room_list, split[0]);
	add_link_room(head, room_add);
	free(split[0]);
	free(split[1]);
	free(split);
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
		{
			free(new_line);
			continue ;
		}
		else
			break ;
	}
	free(new_line);
	return (1);
}

t_room_list *get_end(t_room_list *room_list)
{
	while (room_list->room->is_end != 1 && room_list != NULL)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	room_list->room->is_set = 1;
	return (room_list);
}

t_queue *new_queue(t_room *room, int dist)
{
	t_queue *queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = room;
	queue->room->dist = dist + 1;
	queue->room->is_set = 1;
	queue->next_room = NULL;
	return (queue);
}

t_queue *enqueue(t_queue *queue, t_room *room, t_room_list *current)
{
	t_queue *head;
	head = queue;

	if (queue == NULL)
		return (new_queue(room, current->room->dist));
	while (queue->next_room != NULL)
		queue = queue->next_room;
	queue->next_room = new_queue(room, current->room->dist);
	return (head);
}

t_queue *dequeue(t_queue *queue)
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

int set_distance(t_room_list *room_list)
{
	t_room_list *head;
	t_room_list *current;
	t_queue *queue;

	queue = NULL;
	head = room_list;
	current = get_end(head);
	while (current)
	{
		room_list = current->next_room;
		while (room_list)
		{
			if (room_list->room->is_set == 0)
				queue = enqueue(queue, room_list->room, current);
			room_list = room_list->next_room;
		}
		if (queue == NULL)
			return (1);
		current = get_room_list_head(head, queue->room->name);
		queue = dequeue(queue);
	}
	return (1);
}

t_room_list *get_start(t_room_list *room_list)
{
	while (room_list->room->is_start != 1 && room_list != NULL)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	return (room_list);
}

int next_move(t_ant *ant, t_room_list *room_list)
{

	return (1);
}

int move_ants(t_ant *ant, t_room_list *room_list)
{
	t_room_list *head;

	head = room_list;
	room_list = get_start(head);
	while (next_move(ant, room_list) == 1)
	{}
	return (1);
}

int set_ants(t_ant *ant, t_room_list *room_list)
{
	room_list = get_start(room_list);
	room_list->room->ant = ant;
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
	set_distance(room_list);
	print_room_list(room_list);
	set_ants(ants, room_list);
	move_ants(room_list);
	// NEED TO FREE ROOMS AND ROOM LIST BEFORE EXIT
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
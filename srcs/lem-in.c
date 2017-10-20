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
	head->at_end = 0;
	head->current_room = NULL;
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
		new->at_end = 0;
		new->current_room = NULL;
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
		ft_printf("%s\n", line);
		if (ret > 0)
		{
			if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
				break ;
			else if (line[0] == '#')
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
	{
		g_start++;
		start = 1;
	}
	else if (ft_strstr(line, "##end"))
	{
		g_end++;
		end = 1;
	}
	if (g_end > 1 || g_start > 1)
		return (NULL);
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
	ft_printf("%s\n", line);
	if (line[0] == '#' || ft_strstr(line, "-") || line[1] == '#')
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
	int links;
	t_room_list *room_list;

	room_list = NULL;
	links = 0;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
		{
			if ((room_list = command(line, room_list)) == NULL)
			{
				return (NULL);
			}
		}
		else if (line[0] == '#')
			continue ;
		else if (!ft_strstr(line, "-"))
		{
			room_list = add_room_list(next_line_room(line), room_list);
		}
		else
		{	
			if ((read_links(line, room_list)) == -1)
			{
				free(line);
				return (NULL);
			}
			links = 1;
			free(line);
			return (room_list);
		}
		// free(line);
	}
	//ft_printf("Line: %s\n", line);
	ft_strdel(&line);
	if (links == 0)
		return (NULL);
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

	if (g_start == 0 || g_end == 0)
		return (-1);
	if (ft_strstr(line, " ") && line[0] != '#')
		return (-1);
	add_link_line(room_list, line);
	while ((ret = get_next_line(0, &new_line)) > 0)
	{
		ft_printf("%s\n", new_line);
		if (ft_strstr(new_line, " ") && new_line[0] != '#')
			return (-1);
		if (new_line[0] == '#' && ret > 0)
		{
			free(new_line);
			continue ;
		}
		else if (ft_strstr(new_line, "-") && ret > 0)
			add_link_line(room_list, new_line);
		else
			return (-1);
	}
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
	current = get_start(head);
	if (current->room->is_set == 0)
		return (-1);
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

int set_ants(t_ant *ant, t_room_list *room_list)
{
	room_list = get_start(room_list);
	while (ant)
	{
		ant->current_room = room_list->room;
		ant = ant->next_ant;
	}
	return (1);
}

int get_size_ants(t_ant *ant)
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

// t_room *get_min_dist(t_room_list *room_list)
// {
// 	int min;
// 	t_room *go;

// 	min = room_list->room->dist;
// 	room_list = room_list->next_room;
// 	if (room_list == NULL)
// 		return (NULL);
// 	go = room_list->room;
// 	while (room_list)
// 	{
// 		//ft_printf("Room min: %s\n", room_list->room->name);
// 		if (room_list->room->dist < min && room_list->room->is_occupied == 0)
// 		{
// 			min = room_list->room->dist;
// 			go = room_list->room;
// 		}
// 		room_list = room_list->next_room;
// 	}
// 	if (go->is_occupied == 1)
// 		return (NULL);
// 	return (go);
// }

t_room *get_min_dist(t_room_list *room_list)
{
	t_room *go;
	t_room_list *src;

	src = room_list;
	room_list = room_list->next_room;
	if (room_list == NULL)
		return (NULL);
	go = room_list->room;
	while (room_list)
	{
		if (room_list->room->dist < src->room->dist && room_list->room->is_occupied == 0)
			go = room_list->room;
		room_list = room_list->next_room;
	}
	if (go->is_occupied == 0 && go->dist < src->room->dist)
		return (go);
	return (NULL);
}

t_room *check_move(t_ant *ant, t_room_list *room_list)
{
	t_room_list *check_links;
	t_room *go;

	check_links = get_room_list_head(room_list, ant->current_room->name);
	go = get_min_dist(check_links);
	return (go);
}

int next_move(t_ant *ant, t_room_list *room_list)
{
	t_room *go;

	while (ant)
	{
		if (ant->has_moved == 0)
		{
			if ((go = check_move(ant, room_list)) != NULL)
			{
				move_ant_room(ant, go);
				if (go->is_end)
					return (-2);
				return (1);
			}
		}
		ant = ant->next_ant;
	}
	//ft_printf("No ants can move\n");
	return (-1);
}

int reset_ants(t_ant *ant)
{
	while (ant)
	{
		if (ant->at_end != 1)
			ant->has_moved = 0;
		ant = ant->next_ant;
	}
	return (1);
}

int move_ant_room(t_ant *ant, t_room *dest)
{
	t_ant *p;
	t_room *src;

	src = ant->current_room;
	if (src->is_start == 0)
		src->is_occupied = 0;
	if (dest->is_end == 1)
	{
		ant->at_end = 1;
		ant->has_moved = 1;
	}
	else
	{
		dest->is_occupied = 1;
		ant->current_room = dest;
		ant->has_moved = 1;
	}
	ft_printf("L%i-%s ", ant->number, dest->name);
	return (1);
}

int move_ants(t_ant *ant, t_room_list *room_list)
{
	int turns;
	int move;

	turns = get_size_ants(ant) * 2;
	while (turns > 0)
	{
		move = turns;
		reset_ants(ant);
		while (move > 0)
			move += (next_move(ant, room_list));
		turns = get_size_ants(ant) * 2;
		ft_printf("\n");
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
	if ((ret = set_distance(room_list)) == -1)
		return (-1);
	//print_room_list(room_list);
	set_ants(ants, room_list);
	ft_printf("\n");
	move_ants(ants, room_list);
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
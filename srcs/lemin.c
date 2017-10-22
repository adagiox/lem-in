#include "../includes/lemin.h"

t_ant *new_ant(t_ant *head, int number)
{
	head = (t_ant *)malloc(sizeof(t_ant));
	head->number = number;
	head->has_moved = 0;
	head->at_end = 0;
	head->current_room = NULL;
	head->next_ant = NULL;
	return (head);
}

t_ant *new_ants(int size)
{
	t_ant *ant;
	t_ant *new;
	t_ant *head;
	int number;

	head = NULL;
	number = 1;
	head = new_ant(head, number);
	number++;
	ant = head;
	while (number < size + 1)
	{
		while (ant->next_ant != NULL)
			ant = ant->next_ant;
		new = new_ant(new, number);
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
		ft_printf("%s\n", line);
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
			break ;
		else if (line[0] == '#')
		{
			ft_strdel(&line);
			continue ;
		}
		break ;
	}
	if (ret == 0 && line == NULL)
		return (NULL);
	size = ft_atoi(line);
	if (size <= 0)
		return (NULL);
	ft_strdel(&line);
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

	if (room == NULL)
		return (NULL);
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
	new->head_room = NULL;
	new->is_occupied = 0;
	new->is_start = start;
	new->is_end = end;
	return (new);
}

int	check_line_split(char **split)
{
	int size;

	size = 0;
	while (split)
	{
		size++;
		split++;
	}
	if (size != 2)
		return (-1);
	return (1);
}

int count_split(char **split)
{
	int i;
	int size;

	size = 0;
	i = 0;
	while (split[i])
	{
		if (i == 1 || i == 2)
		{
			if (ft_isdigit(split[i][0]) == 0)
				return (-1);
		}
		i++;
		size++;
	}
	return (size);
}

int free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	return (1);
}

int	check_room_split(char **split)
{
	int size;

	size = count_split(split);
	if (size != 3)
	{
		free_split(split);
		free(split);
		return (-1);
	}
	return (1);
}

t_room *next_room(unsigned int start, unsigned int end)
{
	char *line;
	char **split;
	t_room *room;
	int ret;

	if ((ret = get_next_line(0, &line)) <= 0)
	{
		ft_strdel(&line);
		return (NULL);
	}
	ft_printf("%s\n", line);
	if (line[0] == '#' || ft_strstr(line, "-") || line[1] == '#' ||
		line[0] == 'L')
	{
		ft_strdel(&line);
		return (NULL);
	}
	split = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (check_room_split(split) == -1)
		return (NULL);
	room = new_room(start, end, split);
	free_split(split);
	free(split);
	return (room);
}

t_room *next_line_room(char *line)
{
	t_room *room;
	char **split;

	split = ft_strsplit(line, ' ');
	if (check_room_split(split) == -1)
		return (NULL);
	room = new_room(0, 0, split);
	free_split(split);
	free(split);
	return (room);
}

t_room_list *read_rooms_read_links(t_room_list *room_list, char *line)
{
	if ((read_links(line, room_list)) == -1)
		return (NULL);
	ft_strdel(&line);
	return (room_list);
}

t_room_list *read_rooms_command(t_room_list *room_list, char *line)
{
	if ((room_list = command(line, room_list)) == NULL)
	{
		ft_strdel(&line);
		return (NULL);
	}
	return (room_list);
}

int check_l(char *line)
{
	if (line[0] == 'L')
	{
		ft_strdel(&line);
		return (-1);
	}
	return (1);
}

t_room_list *read_rooms_room_list(t_room_list *room_list, char *line)
{
	t_room *room_add;

	if (!ft_strstr(line, "-"))
	{
		if (check_l(line) == -1)
			return (NULL);
		room_add = next_line_room(line);
		if ((room_list = add_room_list(room_add, room_list)) == NULL)
		{
			ft_strdel(&line);
			return (NULL);
		}
	}
	return (room_list);
}

t_room_list *read_rooms()
{
	char *line;
	int ret;
	t_room_list *room_list;

	room_list = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
		{
			if ((room_list = read_rooms_command(room_list, line)) == NULL)
				return (NULL);
		}
		else if (check_hash(line) == 1)
			continue ;
		else if (!ft_strstr(line, "-"))
		{
			if ((room_list = read_rooms_room_list(room_list, line)) == NULL)
				return (NULL);
		}
		else
			return (read_rooms_read_links(room_list, line));
		ft_strdel(&line);
	}
	return (room_list);
}

t_room *get_link_room(t_room_list *room_list, char *name)
{
	while (room_list != NULL && (ft_strcmp(room_list->room->name, name)) != 0)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	if (room_list->room->head_room == NULL)
		room_list->room->head_room = room_list;
	return (room_list->room);
}

t_room_list *get_room_list_head(t_room_list *room_list, char *name)
{
	if (room_list == NULL || name == NULL)
		return (NULL);
	while (room_list != NULL &&(ft_strcmp(room_list->room->name, name)) != 0)
		room_list = room_list->next_room_list;
	if (room_list == NULL)
		return (NULL);
	return (room_list);
}

t_room_list *get_room_list(t_room *room)
{
	if (room == NULL)
		return (NULL);
	return (room->head_room);
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

int check_link_error(t_room_list *room_list, char *line)
{
	if (g_start == 0 || g_end == 0 || (ft_strstr(line, " ") && line[0] != '#')
		|| (add_link_line(room_list, line)) == 0)
	{
		ft_strdel(&line);
		return (-1);
	}
	return (1);
}

int check_link_space(char *new_line)
{
	if (ft_strstr(new_line, " ") && new_line[0] != '#')
	{
		ft_strdel(&new_line);
		return (-1);
	}
	return (1);
}

int check_hash(char *new_line)
{
	if (new_line[0] == '#')
	{
		ft_strdel(&new_line);
		return (1);
	}
	return (-1);
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

t_room *check_move(t_ant *ant)
{
	t_room_list *check_links;
	t_room *go;

	check_links = get_room_list(ant->current_room);
	go = get_min_dist(check_links);
	return (go);
}

int next_move(t_ant **ant)
{
	t_room *go;
	t_ant *current;

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

int reset_ants(t_ant *ant)
{
	while (ant)
	{
		ant->has_moved = 0;
		ant = ant->next_ant;
	}
	return (1);
}

int move_ant_room(t_ant **ant, t_ant *current, t_room *dest)
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

int get_moves(int n, t_room_list *room_list)
{
	int moves;

	room_list = get_start(room_list);
	moves = room_list->room->dist * 5;
	if (room_list->room->dist == 1)
		moves = n;
	return (moves);
}

int move_ants(t_ant **ant, t_room_list *room_list)
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

int	lemin()
{
	t_ant *ants;
	t_room_list *room_list;

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
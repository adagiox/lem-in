#include "../includes/lem-in.h"

void print_ants(t_ant *ant)
{
	while (ant != NULL)
	{
		ft_printf("Ant: %i\t\tMoved: %u\n", ant->number, ant->has_moved);
		ant = ant->next_ant;
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

int add_room(t_room_list *room_list, unsigned int start, unsigned int end)
{

	return (1);
}

int command(char *line, t_room_list *room_list)
{
	char *new_line;
	unsigned int start;
	unsigned int end;

	start = 0;
	end = 0;
	if (ft_strstr(line, "##start"))
		start = 1;
	else if (ft_strstr(line, "##end"))
		end = 1;
	add_room(room_list, start, end);
	return (1);
}

int next_room(t_room_list *room_list)
{

}

t_room_list *read_rooms()
{
	char *line;
	int ret;
	t_room_list *room_list;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
			command(line, room_list);
		else if (line[0] == '#')
			continue ;
	}
	if (ret <= 0)
		return (NULL);
	// read_links(room_list);
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
	if ((room_list = read_rooms()) == NULL)
		return (-1);
	
	print_ants(ants);
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
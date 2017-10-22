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
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

t_ant *init_ants(char *line)
{
	t_ant *ant;
	int size;

	size = ft_atoi(line);
	ft_printf("size: %i\n", size);
	ant = new_ants(size);
	return (ant);
}

int	lemin()
{
	char *line;
	int ret;
	t_ant *ant;

	ret = 1;
	ret = get_next_line(0, &line);
	ant = init_ants(line);
	print_ants(ant);
	return (1);
}

int main(void)
{
	lemin();
	return (0);
}
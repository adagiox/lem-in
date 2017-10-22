#include "../includes/lemin.h"

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

int check_l(char *line)
{
	if (line[0] == 'L')
	{
		ft_strdel(&line);
		return (-1);
	}
	return (1);
}
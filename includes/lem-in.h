#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"

typedef struct	s_ant
{
	int				number;
	unsigned int	has_moved:1;
	struct s_ant	*next_ant;
}				t_ant;

typedef struct	s_room
{
	char			*name;
	int				dist;
	int				x;
	int				y;
	t_ant			*ant;
	unsigned int	is_occupied:1;
	unsigned int	is_start:1;
	unsigned int	is_end:1;
	struct s_room	*next_room;
}				t_room;

typedef struct	s_room_list
{
	t_room				*room;
	struct s_room_list	*next_room_list;
}				t_room_list;

void print_ants(t_ant *ant);
void print_room_list(t_room_list *room_list);
t_ant *new_ants(int size);
t_ant *read_ants();
t_room_list *new_room_list(t_room *room);
t_room_list *add_room_list(t_room *room, t_room_list *room_list);
t_room_list *command(char *line, t_room_list *room_list);
t_room *new_room(unsigned int start, unsigned int end, char **room);
t_room *next_room(unsigned int start, unsigned int end);
t_room_list *read_rooms();
int	lemin();


#endif
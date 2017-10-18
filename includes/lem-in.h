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
	t_ant			*ant;
	unsigned int	is_occupied:1;
	unsigned int	is_start:1;
	unsigned int	is_end:1;
}				t_room;

typedef struct	s_room_list
{
	t_room	*head;
	t_room	*next_room;
}				t_room_list;

#endif
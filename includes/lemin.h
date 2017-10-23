/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:07:27 by erintala          #+#    #+#             */
/*   Updated: 2017/10/22 17:07:29 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/includes/libft.h"

typedef struct	s_ant
{
	int					number;
	unsigned int		has_moved:1;
	unsigned int		at_end:1;
	struct s_room		*current_room;
	struct s_ant		*next_ant;
}				t_ant;

typedef struct	s_room
{
	char				*name;
	int					dist;
	unsigned int		is_set:1;
	int					x;
	int					y;
	t_ant				*ant;
	struct s_room_list	*head_room;
	unsigned int		is_occupied:1;
	unsigned int		is_start:1;
	unsigned int		is_end:1;
}				t_room;

typedef struct	s_room_list
{
	t_room				*room;
	struct s_room_list	*next_room;
	struct s_room_list	*next_room_list;
}				t_room_list;

typedef struct	s_queue
{
	t_room				*room;
	struct s_queue		*next_room;
}				t_queue;

int				g_start;
int				g_end;

t_ant			*new_ants(int size);
t_ant			*new_ants(int size);
t_ant			*read_ants();
t_room_list		*new_room_list(t_room *room);
t_room_list		*add_room_list(t_room *room, t_room_list *room_list);
t_room_list		*command(char *line, t_room_list *room_list);
t_room			*new_room(unsigned int start, unsigned int end, char **room);
int				check_line_split(char **split);
int				count_split(char **split);
int				free_split(char **split);
int				check_room_split(char **split);
t_room			*next_room(unsigned int start, unsigned int end);
t_room			*next_line_room(char *line);
t_room_list		*read_rooms_read_links(t_room_list *room_list, char *line);
t_room_list		*read_rooms_command(t_room_list *room_list, char *line);
int				check_l(char *line);
t_room_list		*read_rooms_room_list(t_room_list *room_list, char *line);
t_room_list		*read_rooms();
t_room			*get_link_room(t_room_list *room_list, char *name);
t_room_list		*get_room_list_head(t_room_list *room_list, char *name);
t_room_list		*get_room_list(t_room *room);
t_room_list		*new_link_next_room(t_room *new_link_room);
int				add_link_room(t_room_list *room_list_head,
					t_room *new_link_room);
int				add_link_line(t_room_list *room_list, char *line);
int				check_link_error(t_room_list *room_list, char *line);
int				check_link_space(char *new_line);
int				read_links_add_link_line(t_room_list *room_list,
					char *new_line);
int				set_distance(t_room_list *room_list);
int				read_links(char *line, t_room_list *room_list);
int				lemin();
int				check_hash(char *new_line);
int				move_ant_room(t_ant **ant, t_ant *current, t_room *dest);
t_room_list		*get_start(t_room_list *room_list);
t_room_list		*get_end(t_room_list *room_list);
t_queue			*new_queue(t_room *room, int dist);
t_queue			*enqueue(t_queue *queue, t_room *room, t_room_list *current);
t_queue			*dequeue(t_queue *queue);
int				set_ants(t_ant *ant, t_room_list *room_list);
int				get_size_ants(t_ant *ant);
t_room			*get_min_dist(t_room_list *room_list);
t_room			*check_move(t_ant *ant);
int				next_move(t_ant **ant);
int				reset_ants(t_ant *ant);
int				move_ant_room(t_ant **ant, t_ant *current, t_room *dest);
int				get_moves(int n, t_room_list *room_list);
int				move_ants(t_ant **ant, t_room_list *room_list);
void			free_rooms(t_room_list *temp);
int				free_room_list(t_room_list *room_list);

#endif

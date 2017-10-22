FILES = srcs/lemin.c srcs/free_rooms.c srcs/move_ants.c srcs/setup_ants.c \
		srcs/check_links.c srcs/read_links.c srcs/make_ants.c srcs/read_rooms.c \
		srcs/check_rooms.c srcs/set_distance.c srcs/get_rooms.c srcs/setup_rooms.c

all:
	make -C ./libft
	gcc -o lem-in $(FILES) -L./libft -lft -Wall -Werror -Wextra

debug:
	gcc $(FILES) -L./libft -lft -g
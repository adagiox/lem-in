all:
	make -C ./libft
	gcc -o lem-in srcs/lemin.c -L./libft -lft -Wall -Werror -Wextra

debug:
	gcc srcs/lemin.c -L./libft -lft -g
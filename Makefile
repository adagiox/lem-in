all:
	make -C ./libft
	gcc -o lem-in srcs/lem-in.c -L./libft -lft -Wall -Werror -Wextra

debug:
	gcc srcs/lem-in.c -L./libft -lft -g
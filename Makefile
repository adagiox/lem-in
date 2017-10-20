all:
	make -C ./libft
	gcc srcs/lem-in.c -L./libft -lft

debug:
	gcc srcs/lem-in.c -L./libft -lft -g -fsanitize=address
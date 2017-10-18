all:
	make -C ./libft
	gcc srcs/lem-in.c -L./libft -lft
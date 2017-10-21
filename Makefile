all:
	make -C ./libft
	gcc -o lem-in srcs/lem-in.c -L./libft -lft -fsanitize=address

debug:
	gcc srcs/lem-in.c -L./libft -lft -g
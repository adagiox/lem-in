NAME = libft.a

FLAGS = -Wall -Werror -Wextra -I. -c

SRC = 	ft_strncpy.c ft_strcpy.c ft_strdup.c ft_strcat.c ft_strncat.c ft_strcmp.c \
		ft_strncmp.c ft_tolower.c ft_toupper.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_atoi.c ft_isascii.c ft_strlen.c \
		ft_strchr.c ft_strstr.c ft_strnstr.c  ft_strrchr.c ft_memcpy.c ft_strlcat.c \
		ft_bzero.c ft_memcmp.c ft_memchr.c ft_memset.c ft_memccpy.c ft_memmove.c \
		ft_strclr.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_striter.c \
		ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strsplit.c ft_putchar.c ft_putstr.c \
		ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstnew.c ft_lstadd.c ft_lstdelone.c ft_lstdel.c \
		ft_lstiter.c ft_lstmap.c cast_int.c convert.c convert_wc.c format_hex.c \
		format_int.c format_oct.c format_uint.c ft_printf.c handle_percent.c \
		libft_digits.c libft_nbrprint.c libft_print.c libft_wprint.c print_helpers.c \
		print_str.c setup.c get_next_line.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	@echo "Compiling..."
	@gcc $(FLAGS) $(SRC)
	@echo "Archiving..."
	@ar rcs $(NAME) $(OBJ)
	@echo "$(NAME) has been created successfully."

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re

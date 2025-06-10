# --- VARS ---

NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror -g
DEBUGFLAGS = $(FLAGS) -fsanitize=address
P_OBJ = .obj/
P_SRC = src/
# --- SRC ---

SRC = ft_ctype.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c \
ft_lst_functions1.c ft_lst_functions2.c \
ft_is_in.c ft_put_ul_base.c ft_putchar.c ft_printf.c \
ft_putnbr_base.c \
ft_get_next_line_utils.c ft_get_next_line.c ft_strnlen.c \
ft_concat.c ft_create_random_str.c ft_heap_add_suffix.c \
ft_is_non_empty.c ft_multifree.c ft_print_arr.c ft_str_is_alnum.c \
ft_string_arr_utils.c

# --- RULES ---

OBJ = $(addprefix $(P_OBJ), $(SRC:%.c=%.o))

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(P_OBJ)%.o: $(P_SRC)%.c libft.h | $(P_OBJ)
	$(CC) $(FLAGS) -I ./ -c $< -o $@

$(P_OBJ):
	mkdir $(P_OBJ)


clean:
	rm -rf $(P_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

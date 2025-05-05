.PHONY: all clean fclean re

NAME = test
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c test.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c test.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -lreadline -lhistory $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

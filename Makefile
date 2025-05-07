# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 13:36:15 by kbarru            #+#    #+#              #
#    Updated: 2025/04/29 15:02:00 by kbarru           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src/
OBJ_DIR = .obj/
INC_DIR = inc/
TEST_DIR = test/

SRC = main.c env/env.c debug.c
TEST_SRC = test.c
LIBS = -L$(LIB_DIR) -lft -lreadline -lhistory
INCLUDES = $(INC_DIR)minishell.h
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o)) 

LIB_DIR = lib/libft/

.PHONY = all clean fclean re lib test

all : $(NAME)

$(NAME) : $(OBJ) $(LIB_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INCLUDES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR) -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)env

$(LIB_DIR)libft.a :
	$(MAKE) -C $(LIB_DIR)

clean :
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

fclean :	clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -rf $(NAME)

test : all

re : fclean
	$(MAKE) all

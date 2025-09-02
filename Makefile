DEPS = $(OBJ:.o=.d)
NAME = minishell
CC = cc
DEBUG = 1
CFLAGS = -Wall -Wextra -Werror -g -DDEBUG=$(DEBUG)
CPPFLAGS = -Iinc/ -Ilib/libft/inc -MMD -MP

###### SOURCE AND OBJ #####


SRC_DIR = src/
OBJ_DIR = .build/
INC_DIR = inc/

ENV_SRC = env_init.c env_utils.c no_env.c envlist_utils.c 
HISTORY_SRC = history.c
LEXING_SRC = lexing.c lexing_utils.c expand.c expand_utils.c expand_check.c token.c id_token.c quotes.c
BUILTINS_SRC = echo.c cd.c pwd.c export.c unset.c env.c exit.c export_utils.c cd_utils.c cd_symlink.c
PARSING_SRC = parsing.c parsing_utils.c exec_node.c double_input_redir.c
EXEC_SRC = builtins_call.c execute_pipeline.c exec_utils.c exec_children_utils.c execution.c
MAIN_SRC = initial_formatting.c main.c prompt.c ms_utils.c
SIGNALS_SRC = signals.c

ENV_SRC_DIR = env/
HISTORY_SRC_DIR = history/
LEXING_SRC_DIR = lexing/
BUILTINS_SRC_DIR = builtins/
PARSING_SRC_DIR = parsing/
EXEC_SRC_DIR = exec/
SIGNALS_DIR = signals/
LIB_DIR = lib/libft/
MAIN_DIR = main/

P_ENV = $(addprefix $(ENV_SRC_DIR), $(ENV_SRC))
P_HISTORY = $(addprefix $(HISTORY_SRC_DIR), $(HISTORY_SRC))
P_LEXING = $(addprefix $(LEXING_SRC_DIR), $(LEXING_SRC))
P_BUILTINS = $(addprefix $(BUILTINS_SRC_DIR), $(BUILTINS_SRC))
P_PARSING = $(addprefix $(PARSING_SRC_DIR), $(PARSING_SRC))
P_EXEC = $(addprefix $(EXEC_SRC_DIR), $(EXEC_SRC))
P_SIGNALS = $(addprefix $(SIGNALS_DIR), $(SIGNALS_SRC))
P_MAIN = $(addprefix $(MAIN_DIR), $(MAIN_SRC))

SRC = $(P_ENV) $(P_HISTORY) $(P_LEXING) $(P_BUILTINS) $(P_PARSING) $(P_EXEC) $(P_SIGNALS) $(P_MAIN)
TEST_SRC = test.c
LIBS = -L$(LIB_DIR) -lft -lreadline -lhistory
R_INCLUDES = minishell.h color.h exec.h parsing.h lexing.h history.h signals.h builtins.h data_structures.h env.h error.h prompt.h ms_utils.h
INCLUDES = $(addprefix $(INC_DIR), $(R_INCLUDES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o)) 
TOBJ = $(filter-out $(OBJ_DIR)main.o, $(OBJ))

.PHONY = all clean fclean re lib test

all : libft $(NAME)

libft :
	$(MAKE) -C $(LIB_DIR)

$(NAME) : $(OBJ) $(LIB_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INC_DIR) -I$(LIB_DIR) -c $< -o $@

-include $(DEPS)

##### DIRECTORIES #####


$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(ENV_SRC_DIR)
	mkdir -p $(OBJ_DIR)$(HISTORY_SRC_DIR)
	mkdir -p $(OBJ_DIR)$(LEXING_SRC_DIR)
	mkdir -p $(OBJ_DIR)$(BUILTINS_SRC_DIR)
	mkdir -p $(OBJ_DIR)$(PARSING_SRC_DIR)
	mkdir -p $(OBJ_DIR)$(EXEC_SRC_DIR)
	mkdir -p $(OBJ_DIR)$(SIGNALS_DIR)
	mkdir -p $(OBJ_DIR)$(MAIN_DIR)

##### LIB #####

$(LIB_DIR)libft.a :
	$(MAKE) -C $(LIB_DIR)

##### PHONY #####

clean :
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(UNITY_OBJ_DIR)

fclean :	clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -rf $(NAME)

re : fclean
	$(MAKE) all


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEBUG_FLAGS = -Wall -Wextra -g -fsanitize=address

##### TESTS #####

UNITY_OBJ_DIR = .unity_obj/
UNITY_DIR = test/unity/src/
UNITY_H = unity.h
UNITY_SRC = unity.c
UNITY_FSRC = $(addprefix $(UNITY_DIR), $(UNITY_SRC))

UNITY_INCS = $(addprefix $(UNITY_DIR), $(UNITY_H) $(UNITY_C))
TEST_DIR = test/
UNITY_OBJ = $(subst $(UNITY_DIR), $(UNITY_OBJ_DIR), $(UNITY_FSRC:%.c=%.o))
TEST_OBJ = $(addprefix $(TEST_DIR), $(TEST_SRC:%.c=%.o))
TEST_SRC = test/test.o
##################

###### SOURCE AND OBJ #####


SRC_DIR = src/
OBJ_DIR = .obj/
INC_DIR = inc/
TEST_DIR = test/


ENV_SRC = env.c env_utils.c
HISTORY_SRC = history.c
LEXING_SRC = lexing.c lexing_utils.c expand.c expand_utils.c token.c id_token.c quotes.c
BUILTINS_SRC = echo.c cd.c pwd.c export.c unset.c env.c exit.c export_utils.c
PARSING_SRC = parsing.c parsing_utils.c exec_node.c double_input_redir.c
EXEC_SRC = builtins_call.c envlist_utils.c execute_pipeline.c
SIGNALS_SRC = signals.c

ENV_SRC_DIR = env/
HISTORY_SRC_DIR = history/
LEXING_SRC_DIR = lexing/
BUILTINS_SRC_DIR = builtins/
PARSING_SRC_DIR = parsing/
EXEC_SRC_DIR = exec/
SIGNALS_DIR = signals/
LIB_DIR = lib/libft/

P_ENV = $(addprefix $(ENV_SRC_DIR), $(ENV_SRC))
P_HISTORY = $(addprefix $(HISTORY_SRC_DIR), $(HISTORY_SRC))
P_LEXING = $(addprefix $(LEXING_SRC_DIR), $(LEXING_SRC))
P_BUILTINS = $(addprefix $(BUILTINS_SRC_DIR), $(BUILTINS_SRC))
P_PARSING = $(addprefix $(PARSING_SRC_DIR), $(PARSING_SRC))
P_EXEC = $(addprefix $(EXEC_SRC_DIR), $(EXEC_SRC))
P_SIGNALS = $(addprefix $(SIGNALS_DIR), $(SIGNALS_SRC))

SRC = $(P_ENV) $(P_HISTORY) $(P_LEXING) $(P_BUILTINS) $(P_PARSING) $(P_EXEC) $(P_SIGNALS) main.c debug.c
TEST_SRC = test.c
LIBS = -L$(LIB_DIR) -lft -lreadline -lhistory
INCLUDES = $(INC_DIR)minishell.h
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o)) 
TOBJ = $(filter-out $(OBJ_DIR)main.o, $(OBJ))

.PHONY = all clean fclean re lib test

all : libft $(NAME)

libft :
	$(MAKE) -C $(LIB_DIR)

$(NAME) : $(OBJ) $(LIB_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INCLUDES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR) -c $< -o $@

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

$(UNITY_OBJ_DIR) :
	mkdir -p $(UNITY_OBJ_DIR)

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

mac :
	$(MAKE) all LIBS="-L$(LIB_DIR) -lft -ledit"

asan :
	$(MAKE) re CFLAGS="$(DEBUG_FLAGS)"
	$(MAKE) clean

debug :
	$(MAKE) re CFLAGS+="-D DEBUG=TRUE -g"
	$(MAKE) clean

###### OBJECT FILES ######


$(TEST_DIR)%.o : $(TEST_DIR)%.c $(UNITY_INCS) | $(TEST_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(UNITY_DIR) -I$(LIB_DIR) -c $< -o $@


$(UNITY_OBJ_DIR)%.o : $(UNITY_DIR)%.c | $(UNITY_OBJ_DIR)
	$(CC) -c $< -o $@



######## TESTING #########


testmac : mac $(TEST_OBJ) $(UNITY_OBJ)
	$(CC) $(CFLAGS) $(TOBJ) $(TEST_OBJ) $(UNITY_OBJ) -L$(LIB_DIR) -lft -ledit -o runtest
	chmod +x runtest
	rm $(TEST_OBJ)
	./runtest

test : all $(TEST_OBJ) $(UNITY_OBJ)
	$(CC) $(CFLAGS) $(TOBJ) $(TEST_OBJ) $(UNITY_OBJ) $(LIBS) -lft -o runtest
	chmod +x runtest
	rm $(TEST_OBJ)
	./runtest

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/* note : a TOKEN_FILE can only be after a redirection : in other cases, it is considered a TOKEN_STR, even when it is supposed to refer to a file (i.e the arg after `cat` command) */
typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_OPT,
	TOKEN_STR,
	TOKEN_PIPE,
	TOKEN_REDIRECT,
	TOKEN_FILE,
}	t_token_type;

typedef struct s_token
{
	enum e_token_type	type;
	char				*token;

}						t_token;

typedef struct s_exec_lst
{
	char				**cmd;
	struct s_exec_lst	*next;
}						t_exec_lst;

/* storing env as a linked list is simplifies the implementation of functions that modifiy the environment size, i.e unset, export.... */
typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

// ENV.C
size_t		ft_strlen_c(char str[], char c);
t_env_lst	*create_env_lst(char name[]);
void		env_add_back(t_env_lst **head, t_env_lst *new);
t_env_lst	*create_environment(t_env_lst **env_lst, char *envp[]);
void		print_env(t_env_lst *env_lst);

// DEBUG.c
void		display_token(t_token *token);
void		print_token_list(t_list *tokens);
#endif

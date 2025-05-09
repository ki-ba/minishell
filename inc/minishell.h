#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
# elif __APPLE__
#  include <editline/readline.h>
# endif

# ifndef HIST_FILE
#  define HIST_FILE ".zzsh_history"
# endif

/* note : a TOKEN_FILE can only be after a redirection.
 * in other cases, it is considered a TOKEN_STR,
 * even when it is supposed to refer to a file
 * (i.e the arg after `cat` command) */
typedef enum e_token_type
{
	TOKEN_CMD = 0,
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

/* storing env as a linked list is simplifies the implementation
 * of functions that modifiy the environment size, i.e unset, export.... */
typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}						t_env_lst;

t_env_lst		*create_environment(t_env_lst **env_lst, char *envp[]);
t_env_lst		*create_env_lst(char name[]);
size_t			ft_strlen_c(char str[], char c);
void			env_add_back(t_env_lst **head, t_env_lst *new);
void			print_env(t_env_lst *env_lst);

/* debug.c */
void			display_token(t_token *token);
void			print_token_list(t_list *tokens);

/* history.c */

void			ft_add_history(int hist_fd, char entry[], char last_cmd[]);
int				retrieve_history(char *last_cmd[]);

/* lexing.c */

t_token_type	determine_token_type(char token_str[], t_token_type last_type, t_bool *cmd_bool);
t_token			*create_token(t_list **tokens, char *token_str, t_bool *cmd_bool);
void			tokenize(t_list **tokens, char *line);

/* lexing_utils.c */

int				check_quotes(char *line);
size_t			count_token_len(char *line);
t_bool			determine_redirect(char token_str[]);
t_bool			determine_option(char token_str[]);
t_bool			determine_pipe(char token_str[]);
#endif

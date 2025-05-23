#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_structures.h"
# include <limits.h>

# ifdef __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
# elif __APPLE__
#  include <editline/readline.h>
# endif

# ifndef HIST_FILE
#  define HIST_FILE ".zzsh_history"
# endif

t_env_lst		*create_environment(t_env_lst **env_lst, char *envp[]);
t_env_lst		*create_env_lst(char name[]);
size_t			ft_strlen_c(char str[], char c);
void			env_add_back(t_env_lst **head, t_env_lst *new);
void			print_env(t_env_lst *env_lst);

/* debug.c */
void			display_token(t_token *token);
void			print_token_list(t_list *tokens);
char			*summarize_lexing(t_list *tokens);
/* history.c */

void			ft_add_history(int hist_fd, char entry[], char last_cmd[]);
int				retrieve_history(char *last_cmd[]);

/* lexing.c */

t_token_type	determine_token_type(char token_str[], t_token_type *last_type, t_bool *cmd_bool);
t_token			*create_token(t_list **tokens, char *token_str, t_bool *cmd_bool);
void			tokenize(t_list **tokens, char *line);
void			remove_quotes(void *item);

/* token.c */
void			deltoken(void *token);

/* exec_node.c */
void			del_exec_node(void *node);

/* lexing_utils.c */

int				check_quotes(char *line);
size_t			count_token_len(char *line);
t_bool			determine_redirect(char token_str[]);
t_bool			determine_option(char token_str[]);
t_bool			determine_pipe(char token_str[]);

/* expand.c */

/*static size_t	varnamelen(char str[]);*/
/*static size_t	get_part_len(char str[]);*/
char			*expand_line(t_env_lst *env, char str[]);
t_bool			must_expand(char str[], size_t pos);

/* env.c */

t_env_lst		*create_environment(t_env_lst **env_lst, char *envp[]);
char			**create_env_arr(t_env_lst *env_lst);
void			destroy_env_lst(t_env_lst *env_lst);

/* env_utils.c */

t_env_lst		*create_env_lst(char name[]);
void			env_add_back(t_env_lst **head, t_env_lst *new);
void			print_env(t_env_lst *env_lst);
char			*get_env_val(t_env_lst *env, char name[]);
size_t			get_env_size(t_env_lst *env_lst);

/* parsing.c */

char			**add_to_array(char **arr, char *str);
t_exec_node		*create_exec_node(void);
t_list			*parse_tokens(t_list *tokens);
void			print_exec(t_list	*exec_lst);

#endif

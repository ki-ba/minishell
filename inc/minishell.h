#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_structures.h"
# include "exec.h"
# include "builtins.h"
# include "error.h"
# include <limits.h>
# include <sys/wait.h>

# ifdef __linux__
#  include <readline/readline.h>
#  include <readline/history.h>
# elif __APPLE__
#  include <editline/readline.h>
# endif

# ifndef HIST_FILE
#  define HIST_FILE ".zzsh_history"
# endif

# ifndef DEBUG
#  define DEBUG FALSE
# endif

# ifndef HERE_DOC_LEN
#  define HERE_DOC_LEN 8
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

t_token_type	token_type(char val[], t_token_type *last_type, t_bool *cmd_b);
t_token			*token(t_list **tokens, char *token_str, t_bool *cmd_bool);
int				tokenize(t_list **tokens, char *line);
void			remove_quotes(void *item);

/* quotes.c */

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

char			*expand_line(t_env_lst *env, char str[]);

/* expand_utils.c */

void			join_in_place(char **s1, char *s2);
size_t			varnamelen(char str[]);
size_t			get_part_len(char str[]);
t_bool			must_expand(char str[], size_t pos);
char			*set_chunk_val(t_env_lst *env, char *str, size_t i, size_t len);

/* env.c */

t_env_lst		*create_environment(t_env_lst **env_lst, char *envp[]);
char			**create_env_arr(t_env_lst *env_lst);
void			destroy_env_lst(t_env_lst *env_lst);
t_env_lst		*new_env_entry(char *name, char *value);
void			add_to_env(t_env_lst *env, char *name, char *val, t_bool sh);

/* env_utils.c */

t_env_lst		*create_env_lst(char name[]);
void			env_add_back(t_env_lst **head, t_env_lst *new);
void			print_env(t_env_lst *env_lst);
char			*get_env_val(t_env_lst *env, char name[], int sh);
size_t			get_env_size(t_env_lst *env_lst);

/* parsing.c */

t_exec_node		*create_exec_node(void);
t_list			*parse_tokens(t_list *tokens);
void			print_exec(t_list	*exec_lst);

/* parsing_utils.c */
char			**add_to_array(char **arr, char *str);

/* double_input_redir.c */
int				read_input(char *del);

//TODO: 
int	check_meta_validity(char *str);

/* signals.c */
char			*init_signals(void);

#endif

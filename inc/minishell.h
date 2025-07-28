#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_structures.h"
# include "exec.h"
# include "error.h"
# include "builtins.h"

# include <signal.h>
# include <limits.h>
# include <sys/stat.h>
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

int				exec_unique_cmd(t_list **exec_lst, t_env_lst *env);
t_env_lst		*create_environment(t_env_lst **env_lst, char *envp[]);
size_t			ft_strlen_c(char str[], char c);
void			env_add_back(t_env_lst **head, t_env_lst *new);
void			print_env(t_env_lst *env_lst);
void			update_qm(t_env_lst *env, int status, int conditionnal);
int				is_correct_exit(char *cmd[]);

/* main_utils.c */

void			print_error_msg(int status);
int				wait_processes(pid_t pid, int err);
char			*trim_cmd(char *cmd);
char			*format_cmd(t_env_lst *env, char *cmd);
int				start_execution(t_list *exec, t_env_lst *env, t_bool *is_exit);

/* debug.c */
void			display_token(t_token *token);
void			print_token_list(t_list *tokens);
char			*summarize_lexing(t_list *tokens);
/* history.c */

void			ft_add_history(char entry[]);

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

/* expand_utils_2.c */
int				is_metachar(char c);

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

/* env_utils_2.c */

int				handle_shlvl(t_env_lst *new);

/* parsing.c */

t_exec_node		*create_exec_node(void);
t_list			*parse_tokens(t_list *tokens);
void			print_exec(t_list	*exec_lst);
int				check_parsing(char str[]);

/* parsing_utils.c */
char			**add_to_array(char **arr, char *str);
int				handle_file(t_exec_node *n, t_token *t, t_redir r, t_list **l);

/* double_input_redir.c */
int				read_input(char *del);

//TODO: 
int				check_meta_validity(char *str);

/* signals.c */
void			init_signals(void);
void			update_signals(int redir);

/* expand.c*/
t_bool			is_inquote(char *str, size_t pos);

/* exec_utils.c */

void			next_pipe(t_list **c, t_exec_node *e, int *n, int *p);
void			set_io(t_list **e, t_exec_node *ex, int *n, int *p);
char			*path_to_cmd(char *cmd[], t_env_lst *env);
int				define_error(char path[], t_env_lst *env);
extern int	g_signal; // sig_atomic_t

#endif

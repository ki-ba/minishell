#ifndef EXEC_H
# define EXEC_H

# include "data_structures.h"
# include "libft.h"

/* exec.c */

int		try_exec(t_list **exec, char **cmd, t_env_lst *env);
int		call_cmd(char **cmd, t_env_lst *env);

char	*find_path(char *cmd, t_env_lst *env);
t_bool	is_builtin(char **cmd);

pid_t	exec_pipeline(t_list **exec_lst, t_env_lst **env);
void	exec_child(t_list **cur, t_env_lst **env, int *next_pipe, int pipe[2]);
void	exec_parent(t_exec_node *exe, int *nxt_pipe, int pipe[2]);

/* exec_utils.c */
pid_t	dup_n_fork(t_list **exec, t_list **cur, t_env_lst **env, int *nxt_pip);
char	*path_to_cmd(char *cmd[], t_env_lst *env);
int		define_error(char path[], t_env_lst *env);
void	set_child_io(t_list **exe_ls, t_exec_node *exe, int *nxt_pip, int p[2]);

#endif

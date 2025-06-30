#ifndef EXEC_H
# define EXEC_H

# include "data_structures.h"
# include "libft.h"
/* path.c */

char	**extract_path(t_env_lst *env);

/* exec.c */

int		try_exec(char **cmd, t_env_lst *env);
int		call_cmd(char **cmd, t_env_lst *env);

char	*find_path(char *cmd, t_env_lst *env);
t_bool	is_builtin(char **cmd); //, t_exec_node *exe);

pid_t	exec_pipeline(t_list **exec_lst, t_env_lst *env);
#endif

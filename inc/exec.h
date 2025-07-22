#ifndef EXEC_H
# define EXEC_H

# include "data_structures.h"
# include "libft.h"

/* exec.c */

int		try_exec(t_list **exec, char **cmd, t_env_lst *env);
int		call_cmd(char **cmd, t_env_lst *env);

char	*find_path(char *cmd, t_env_lst *env);
t_bool	is_builtin(char **cmd);

pid_t	exec_pipeline(t_list **exec_lst, t_env_lst *env);
#endif

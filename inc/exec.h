#include "data_structures.h"

/* path.c */

char	**extract_path(t_env_lst *env);

/* exec.c */

char	*find_bin(char **path);
int		try_exec(char **cmd, char **env);
int		simple_cmd(t_exec_node *exe, t_env_lst *env);
int		call_cmd(t_exec_node *exe, t_env_lst *env);

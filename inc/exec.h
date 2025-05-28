#include "data_structures.h"

/* path.c */

char	**extract_path(t_env_lst *env);

/* exec.c */

char	*find_bin(char **path);
int		try_exec(char **cmd, char **env);

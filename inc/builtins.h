#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structures.h"
# include <sys/types.h>

typedef enum bool	t_bool;

int			ft_echo(char **cmd, t_env_lst *env);
int			ft_cd(char **cmd, t_env_lst *env);
int			ft_pwd(char **cmd, t_env_lst *env);
int			ft_export(char **cmd, t_env_lst *env);
int			ft_unset(char **cmd, t_env_lst *env);
int			ft_env(char **cmd, t_env_lst *env);
int			ft_exit(char **cmd, t_env_lst *env);

t_env_lst	*search_env_var(t_env_lst *env, char *var);
char			**envlist_to_arr(t_env_lst *env_lst);
int			check_name_validity(char *name);
t_env_lst	*dup_env(t_env_lst *env);
t_env_lst	*sort_env_var(t_env_lst *env);

int			getsymlink_helper(char **path_parts, char *cmd, size_t len);
int			setup_path_parts(char **path_parts, char *cmd, t_env_lst *env);
int			check_dir_access(char *new_path);
int			update_env(char *new_path, t_env_lst *env);


#endif

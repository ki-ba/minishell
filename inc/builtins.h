#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structures.h"

typedef enum bool	t_bool;

int			ft_echo(char **cmd, t_env_lst *env);
int			ft_cd(char **cmd, t_env_lst *env);
int			ft_pwd(char **cmd, t_env_lst *env);
int			ft_export(char **cmd, t_env_lst *env);
int			ft_unset(char **cmd, t_env_lst *env);
int			ft_env(char **cmd, t_env_lst *env);
int			ft_exit(char **cmd, t_env_lst *env);

t_env_lst	*search_env_var(t_env_lst *env, char *var);
int			builtins_call(char *line, t_env_lst *env);
char			**envlist_to_arr(t_env_lst *env_lst);
int			check_name_validity(char *cmd);
#endif

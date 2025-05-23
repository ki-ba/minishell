#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structures.h"

typedef enum bool	t_bool;

// int			ft_echo(char *str, t_bool *option);
int			ft_cd(char **cmd, t_env_lst *env);
int			ft_pwd(char **cmd);
// int			ft_export(char *name, char *word);
// int			ft_unset(char *name);
// int			ft_env(char *name, char *value);
// int			ft_exit(int	*gc); //garbage collector

t_env_lst	*search_env_var(t_env_lst *env, char *var);
int			builtins_call(char **cmd, t_env_lst *env);

#endif

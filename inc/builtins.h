#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_echo(char *str, t_bool option);
int	ft_cd(char *path);
int	ft_pwd(void);
int ft_export(char *name, char *word);
int ft_unset(char *name);
int	ft_env(char *name, char *value);
int	ft_exit(int	*gc); //garbage collector

#endif
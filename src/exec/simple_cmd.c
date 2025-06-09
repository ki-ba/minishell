#include "minishell.h"

size_t	envlist_len(t_env_lst *env)
{
	size_t		i;
	t_env_lst	*tmp;

	i = 1;
	tmp = env;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**envlist_to_arr(t_env_lst *env_lst)
{
	char		**env;
	t_env_lst	*tmp;
	size_t		i;
	size_t		len;

	tmp = env_lst;
	env = ft_calloc(envlist_len(env_lst), sizeof(char *));
	i = 0;
	while (tmp->next)
	{
		len = ft_strlen(tmp->name);
		len += ft_strlen(tmp->value);
		env[i] = ft_calloc(len + 2, sizeof(char));
		env[i] = ft_concat(3, tmp->name, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

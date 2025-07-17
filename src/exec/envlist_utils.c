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

	tmp = env_lst;
	env = ft_calloc(envlist_len(env_lst), sizeof(char *));
	i = 0;
	while (tmp->next)
	{
		env[i] = ft_concat(3, tmp->name, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

t_env_lst	*search_env_var(t_env_lst *env, char *var)
{
	t_env_lst	*tmp;
	size_t		max_len;

	tmp = env;
	max_len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strlen(tmp->name) > max_len)
			max_len = ft_strlen(tmp->name);
		if (ft_strncmp(tmp->name, var, max_len + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

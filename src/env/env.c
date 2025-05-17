#include "minishell.h"

t_env_lst	*create_environment(t_env_lst **env_lst, char *envp[])
{
	size_t	i;
	char	*name;

	*env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strlen_c(envp[i], '='));
		env_add_back(env_lst, create_env_lst(name));
		++i;
	}
	return (*env_lst);
}

char	**create_env_arr(t_env_lst *env_lst)
{
	size_t		env_size;
	size_t		i;
	char		**env_arr;
	t_env_lst	*current;

	i = 0;
	current = env_lst;
	env_size = get_env_size(env_lst);
	env_arr = ft_calloc(env_size, sizeof(char *));
	while (i < env_size)
	{
		env_arr[i] = ft_concat(3, current->name, "=", current->value);
		current = current->next;
		++i;
	}
	return (env_arr);
}

void	destroy_env_lst(t_env_lst *env_lst)
{
	t_env_lst	*tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
		free(env_lst->name);
		free(env_lst);
		env_lst = tmp;
	}
}

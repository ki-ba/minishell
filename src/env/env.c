#include "data_structures.h"
#include "libft.h"
#include "minishell.h"

t_env_lst	*create_environment(t_env_lst **env_lst, char *envp[])
{
	size_t		i;
	char		*name;
	t_env_lst	*new;

	*env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strlen_c(envp[i], '='));
		new = create_env_lst(name);
		if (!name || !new)
		{
			free(name);
			destroy_env_lst(*env_lst);
			ft_putstr_fd("error creating environment\n", 2);
			return (NULL);
		}
		env_add_back(env_lst, new);
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
	if (!env_arr)
		return (NULL);
	while (i < env_size)
	{
		env_arr[i] = ft_concat(3, current->name, "=", current->value);
		if (!env_arr[i])
		{
			ft_free_arr(env_arr);
			return (NULL);
		}
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

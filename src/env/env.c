#include "minishell.h"

size_t	ft_strlen_c(char str[], char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (str[i] != c)
		return (0);
	return (i);
}

t_env_lst	*create_env_lst(char name[])
{
	t_env_lst	*new;

	new = malloc(sizeof(t_env_lst));
	new->name = name;
	new->value = getenv(name);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env_lst **head, t_env_lst *new)
{
	t_env_lst	*current;

	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_env_lst	*create_environment(t_env_lst **env_lst, char *envp[])
{
	size_t	i;
	char	*name;

	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strlen_c(envp[i], '='));
		env_add_back(env_lst, create_env_lst(name));
		++i;
	}
	return (*env_lst);
}

void	print_env(t_env_lst *env_lst)
{
	ft_printf("ENVIRONMENT VARIABLES\n");
	while (env_lst)
	{
		ft_printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
}

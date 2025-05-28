#include "minishell.h"

t_env_lst	*create_env_lst(char name[])
{
	t_env_lst	*new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
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

void	print_env(t_env_lst *env_lst)
{
	ft_printf("ENVIRONMENT VARIABLES\n");
	while (env_lst)
	{
		ft_printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
}

char	*get_env_val(t_env_lst *env, char name[])
{
	t_env_lst	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(name, current->name, ft_strlen(name) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

size_t	get_env_size(t_env_lst *env_lst)
{
	size_t	i;

	i = 0;
	while (env_lst)
	{
		++i;
		env_lst = env_lst->next;
	}
	return (i);
}

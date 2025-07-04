#include "libft.h"
#include "minishell.h"

t_env_lst	*create_env_lst(char name[])
{
	t_env_lst	*new;

	if (!name)
		return (NULL);
	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = ft_strdup(getenv(name));
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

char	*get_env_val(t_env_lst *env, char name[], int sh)
{
	t_env_lst	*current;

	if (sh)
		name = ft_concat(2, "?", name);
	if (DEBUG)
		ft_printf("looking for %s\n", name);
	current = env;
	if (!name)
		return (NULL);
	while (current)
	{
		if (!ft_strncmp(name, current->name, ft_strlen(name) + 1))
		{
			if (sh)
				free(name);
			return (current->value);
		}
		current = current->next;
	}
	if (sh)
		free(name);
	return (ft_strdup(""));
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

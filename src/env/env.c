/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:17:27 by kbarru            #+#    #+#             */
/*   Updated: 2025/05/15 10:48:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
		if (!ft_strncmp(name, current->name, ft_strlen(name)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

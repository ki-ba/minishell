/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:13 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 14:13:09 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "minishell.h"
#include <limits.h>

int	handle_shlvl(t_env_lst *new)
{
	int	prev_shlvl;

	prev_shlvl = ft_atoi(getenv("SHLVL"));
	new->value = ft_itoa(prev_shlvl + 1);
	if (prev_shlvl < 0 || prev_shlvl >= INT_MAX)
	{
		return (ft_putstr_fd("ERROR : SHLVL too high\n", 2));
		free(new->value);
	}
	else
		return (new->value == NULL);
}

t_env_lst	*create_env_lst(char name[])
{
	t_env_lst	*new;

	if (!name)
		return (NULL);
	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->name = name;
	if (!ft_strncmp(name, "SHLVL", 6))
	{
		if (handle_shlvl(new))
		{
			free(new);
			return (NULL);
		}
	}
	else
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

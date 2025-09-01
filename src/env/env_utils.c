/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:13 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/01 13:24:43 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "minishell.h"
#include "env.h"
#include <limits.h>
#include <stdlib.h>

static int	handle_shlvl(t_env_lst *new)
{
	int		prev_shlvl;
	char	*env_ret;

	env_ret = getenv("SHLVL");
	if (env_ret)
		prev_shlvl = ft_atoi(env_ret);
	else
		prev_shlvl = 0;
	new->value = ft_itoa(prev_shlvl + 1);
	if (prev_shlvl < 0 || prev_shlvl >= INT_MAX)
	{
		return (ft_putstr_fd("ERROR : SHLVL too high\n", 2));
		free(new->value);
		new->value = NULL;
	}
	else
		return (new->value == NULL);
}

t_env_lst	*create_env_lst(char name[])
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->name = ft_substr(name, 0, ft_strlen_c(name, '='));
	if (new->name && !ft_strncmp(new->name, "SHLVL", 6))
		handle_shlvl(new);
	else
	{
		if (!new->name)
			new->value = NULL;
		else
			new->value = ft_strdup(getenv(new->name));
	}
	if (!new->name || !new->value)
	{
		del_env_entry(new);
		return (NULL);
	}
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

char	*get_env_val(t_env_lst *env, char name[])
{
	t_env_lst	*current;

	current = env;
	if (!name)
		return (NULL);
	while (current)
	{
		if (!ft_strncmp(name, current->name, ft_strlen(name) + 1))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

size_t	envlist_len(t_env_lst *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		++i;
		env = env->next;
	}
	return (i);
}

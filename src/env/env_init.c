/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:03:16 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 14:12:41 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"

t_env_lst	*create_environment(t_env_lst **env_lst, char *envp[])
{
	size_t		i;
	char		*name;
	t_env_lst	*new;

	name = NULL;
	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strlen_c(envp[i], '='));
		new = create_env_lst(name);
		if (!name || !new)
		{
			free(name);
			destroy_env_lst(env_lst);
			ft_putstr_fd("error creating environment\n", 2);
			return (NULL);
		}
		env_add_back(env_lst, new);
		if (ft_strncmp(name, "PWD", 4))
			add_to_env(*env_lst, "CURRPATH", new->value, 1);
		++i;
	}
	empty_env_check(env_lst);
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

void	destroy_env_lst(t_env_lst **env_lst)
{
	t_env_lst	*tmp;
	t_env_lst	*cur;

	cur = *env_lst;
	while (cur)
	{
		tmp = cur->next;
		if (cur->value)
		{
			free(cur->value);
			cur->value = NULL;
		}
		free(cur->name);
		cur->name = NULL;
		free(cur);
		cur = tmp;
	}
	*env_lst = NULL;
}

t_env_lst	*new_env_entry(char *name, char *value)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

/** @param sh wether the variable to add is a shell variable (proper to zzsh) 
* or an environment variable. */
void	add_to_env(t_env_lst *env, char *name, char *val, t_bool sh)
{
	t_env_lst	*new;
	t_env_lst	*current;

	if (sh)
		name = ft_concat(2, "?", name);
	if (!env || !name || !val)
		return ;
	current = env;
	new = new_env_entry(name, val);
	if (sh)
		free(name);
	while (current->next)
		current = current->next;
	current->next = new;
}

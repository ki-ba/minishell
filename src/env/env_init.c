/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:03:16 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/01 12:33:46 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include "error.h"
#include <linux/limits.h>

int	get_cur_wd(t_minishell *ms)
{
	char	*env_cwd;

	env_cwd = getenv("PWD");
	if (env_cwd)
		ms->cur_wd = ft_strdup(env_cwd);
	else
		ms->cur_wd = getcwd(ms->cur_wd, PATH_MAX);
	if (!ms->cur_wd)
		return (ERR_ALLOC);
	return (SUCCESS);
}

void	del_env_entry(t_env_lst *entry)
{
	if (!entry)
		return ;
	free(entry->name);
	entry->name = NULL;
	free(entry->value);
	entry->value = NULL;
	free(entry);
}

t_env_lst	*create_environment(t_minishell *ms_data, char *envp[])
{
	size_t		i;
	t_env_lst	*new;

	i = 0;
	get_cur_wd(ms_data);
	while (envp[i])
	{
		new = create_env_lst(envp[i]);
		env_add_back(&ms_data->env, new);
		if (!new || !(ms_data->cur_wd))
		{
			destroy_env_lst(&ms_data->env);
			ft_putstr_fd("error creating environment\n", 2);
			return (NULL);
		}
		++i;
	}
	empty_env_check(ms_data);
	return (ms_data->env);
}

char	**create_env_arr(t_env_lst *env_lst)
{
	size_t		env_size;
	size_t		i;
	char		**env_arr;
	t_env_lst	*current;

	i = 0;
	current = env_lst;
	env_size = envlist_len(env_lst);
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

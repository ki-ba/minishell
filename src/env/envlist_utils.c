/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:24 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/08 11:56:35 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include "signals.h"

void	update_qm(t_minishell *ms, int status, int conditionnal)
{
	int	*qm;

	qm = &ms->error;
	if (!qm)
		return ;
	if (g_signal == 2)
	{
		*qm = 130;
		g_signal = 0;
	}
	if (conditionnal && (status == 0 || *qm > 0))
		return ;
	*qm = status;
}

/**
* @brief takes the env as a linked list and duplicates it into
* @brief a 2D array, usable when calling execve().
* @brief as the array is heap allocated, it must be freed.
*/
char	**envlist_to_arr(t_env_lst *env_lst)
{
	char		**env;
	size_t		i;

	env = ft_calloc(envlist_len(env_lst) + 1, sizeof(char *));
	if (!env)
	{
		ft_putstr_fd("error converting env to array\n", 2);
		return (NULL);
	}
	i = 0;
	while (env && env_lst->next)
	{
		if (env_lst->value)
			env[i] = ft_concat(3, env_lst->name, "=", env_lst->value);
		else
			env[i] = ft_concat(2, env_lst->name, "=");
		if (!env[i])
		{
			ft_putstr_fd("error converting env to array\n", 2);
			ft_free_arr(env);
			return (NULL);
		}
		env_lst = env_lst->next;
		i++;
	}
	return (env);
}

t_env_lst	*search_env_var(t_env_lst *env, char *var)
{
	t_env_lst	*tmp;
	size_t		max_len;

	tmp = env;
	max_len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strlen(tmp->name) > max_len)
			max_len = ft_strlen(tmp->name);
		if (ft_strncmp(tmp->name, var, max_len + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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

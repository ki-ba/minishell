/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:24 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 14:13:36 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include "signals.h"

void	update_qm(int *qm, int status, int conditionnal)
{
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

size_t	envlist_len(t_env_lst *env)
{
	size_t		i;

	if (!env)
		return (0);
	i = 1;
	while (env->next)
	{
		i++;
		env = env->next;
	}
	return (i);
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

	env = ft_calloc(envlist_len(env_lst), sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (env && env_lst->next)
	{
		env[i] = ft_concat(3, env_lst->name, "=", env_lst->value);
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

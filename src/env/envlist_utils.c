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

void	update_qm(t_env_lst *env, int status, int conditionnal)
{
	t_env_lst	*qm;

	qm = search_env_var(env, "?");
	if (g_signal == 2)
	{
		free(qm->value);
		qm->value = ft_itoa(130);
		g_signal = 0;
	}
	if (conditionnal && (status == 0 || ft_atoi(qm->value) > 0))
		return ;
	free(qm->value);
	qm->value = ft_itoa(status);
}

size_t	envlist_len(t_env_lst *env)
{
	size_t		i;
	t_env_lst	*tmp;

	i = 1;
	tmp = env;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**envlist_to_arr(t_env_lst *env_lst)
{
	char		**env;
	t_env_lst	*tmp;
	size_t		i;

	tmp = env_lst;
	env = ft_calloc(envlist_len(env_lst), sizeof(char *));
	i = 0;
	while (tmp->next)
	{
		env[i] = ft_concat(3, tmp->name, "=", tmp->value);
		if (!env[i])
		{
			ft_putstr_fd("error converting env to array", 2);
			ft_free_arr(env);
			break ;
		}
		tmp = tmp->next;
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

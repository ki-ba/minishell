/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:31:12 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/30 12:48:23 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*dup_env(t_env_lst *env)
{
	t_env_lst	*dup;
	t_env_lst	*tmp;
	t_env_lst	*cpy;

	if (!env)
		return (NULL);
	tmp = env;
	dup = NULL;
	while (tmp)
	{
		if (tmp->name)
		{
			cpy = new_env_entry(tmp->name, tmp->value);
			env_add_back(&dup, cpy);
		}
		tmp = tmp->next;
	}
	tmp = NULL;
	return (dup);
}

static void	swap_nodes(t_env_lst **head, t_env_lst *prev,
						t_env_lst *n1, t_env_lst *n2)
{
	if (!n1 || !n2)
		return ;
	n1->next = n2->next;
	n2->next = n1;
	if (prev)
		prev->next = n2;
	else
		*head = n2;
}

t_env_lst	*sort_env_var(t_env_lst *env)
{
	int			is_sorted;
	t_env_lst	*prev;
	t_env_lst	*tmp;

	if (!env)
		return (NULL);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		tmp = env;
		prev = NULL;
		while (tmp && tmp->next)
		{
			if (ft_strncmp(tmp->name, tmp->next->name,
					ft_strlen(tmp->name) + 1) > 0)
			{
				swap_nodes(&env, prev, tmp, tmp->next);
				is_sorted = 0;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:30:51 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/23 10:31:06 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "minishell.h"
#include <stdlib.h>

static void	del_env_node(t_env_lst *env, t_env_lst *node);

int	ft_unset(char **cmd, t_env_lst *env)
{
	size_t		i;
	t_env_lst	*del;

	i = 0;
	while (cmd[++i])
	{
		if (check_name_validity(cmd[i]))
			continue ;
		del = search_env_var(env, cmd[i]);
		if (!del)
			continue ;
		del_env_node(env, del);
	}
	return (SUCCESS);
}

static void	del_env_node(t_env_lst *env, t_env_lst *node)
{
	t_env_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			free(node->name);
			free(node->value);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
}

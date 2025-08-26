/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:30:51 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/26 18:32:44 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "error.h"
#include "env.h"

static void	del_env_node(t_minishell *ms_data, t_env_lst *node);

int	ft_unset(char **cmd, t_minishell *ms_data)
{
	size_t		i;
	t_env_lst	*del;

	i = 0;
	while (cmd[++i])
	{
		if (check_name_validity(cmd[i]))
			continue ;
		del = search_env_var(ms_data->env, cmd[i]);
		if (!del)
			continue ;
		del_env_node(ms_data, del);
	}
	return (SUCCESS);
}

static void	del_env_node(t_minishell *ms_data, t_env_lst *node)
{
	t_env_lst	*tmp;

	tmp = ms_data->env;
	if (tmp == node)
	{
		ms_data->env = ms_data->env->next;
		tmp = node->next;
		free(node->name);
		free(node->value);
		free(node);
		return ;
	}
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

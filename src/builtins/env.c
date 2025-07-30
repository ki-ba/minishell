/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:03:49 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/30 12:45:23 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **cmd, t_env_lst *env)
{
	t_env_lst	*tmp;

	if (cmd[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (ERR_ARGS);
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->value && check_name_validity(tmp->name) == SUCCESS)
		{
			if (printf("%s=%s\n", tmp->name, tmp->value) == -1)
				return (ERR_PRINT);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_name_validity(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (ERR_ARGS);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (ERR_ARGS);
		i++;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:04:44 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/23 10:06:56 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit_arg(char **cmd);

int	ft_exit(char **cmd, t_env_lst *env)
{
	unsigned int	ret;

	if (!cmd[1])
		ret = ft_atoi(get_env_val(env, "?", 0));
	else
	{
		ret = check_exit_arg(cmd);
		if (ret != SUCCESS)
			return (ret);
		ret = ft_atoi(cmd[1]) % 256;
	}
	return (ret);
}

static int	check_exit_arg(char **cmd)
{
	size_t	i;

	if (cmd[2])
	{
		printf("exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		return (ERR_ARGS);
	}
	i = 0;
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i] && ft_isdigit(cmd[1][i]))
		i++;
	if (cmd[1][i] != '\0')
	{
		ft_printf_fd
			(2, "minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (ERR_PARSING);
	}
	return (SUCCESS);
}

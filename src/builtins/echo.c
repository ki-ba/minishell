/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:04:31 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 13:04:33 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	has_option(char **cmd, char opt)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (!cmd[i] || cmd[i][0] != '-' || (cmd[i][0] == '-' && cmd[i][1] != 'n'))
		return (1);
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][j] == '-' && cmd[i][j + 1] == opt)
			++j;
		while (cmd[i][j])
		{
			if (cmd[i][j] != opt)
				return (i);
			++j;
		}
		++i;
	}
	return (i);
}

int	ft_echo(char **cmd, t_env_lst *env)
{
	size_t	i;
	size_t	opt;

	(void) env;
	opt = has_option(cmd, 'n');
	i = opt;
	while (i && cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i] && cmd[i + 1])
			printf(" ");
		++i;
	}
	if (opt == 1)
		printf("\n");
	return (SUCCESS);
}

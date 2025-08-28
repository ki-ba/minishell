/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:04:31 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/29 01:21:44 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "libft.h"
#include "data_structures.h"
#include "error.h"

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

int	ft_echo(char **cmd, t_minishell *ms_data)
{
	size_t	i;
	size_t	opt;

	(void) ms_data;
	opt = has_option(cmd, 'n');
	i = opt;
	while (i && cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i] && cmd[i + 1])
			ft_putstr_fd(" ", 1);
		++i;
	}
	if (opt == 1)
		printf("\n");
	return (SUCCESS);
}

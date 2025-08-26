/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:28 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/25 13:04:36 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/history.h>

void	ft_add_history(char entry[])
{
	static char	last_cmd[255];

	// if (ft_strlen(entry) > 255)
	// {
	// 	ft_printf_fd(2, "warning : command is very long. \n");
	// 	ft_printf_fd(2, "not adding it to history to avoid add_history\n");
	// 	ft_printf_fd(2, "memory errors.\n");
	// }
	last_cmd = minishell_data->last_cmd;
	if (entry)
	{
		if (!last_cmd || ft_strncmp(entry, last_cmd, ft_strlen(entry) + 1))
		{
			add_history(entry);
			free(last_cmd);
			minishell_data->last_cmd = ft_strdup(entry);
			if (minishell_data->last_cmd == NULL)
				return (ERR_ALLOC);
		}
	}
}

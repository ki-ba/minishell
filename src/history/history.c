/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:28 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/06 18:01:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include <readline/history.h>
#include "data_structures.h"

int	ft_add_history(t_minishell *minishell_data, char entry[])
{
	char	*last_cmd;

	last_cmd = minishell_data->last_cmd;
	if (last_cmd)
	{
		if (entry)
		{
			if (ft_strncmp(entry, last_cmd, ft_strlen(entry) + 1))
			{
				add_history(entry);
				free(last_cmd);
				minishell_data->last_cmd = ft_strdup(entry);
				if (minishell_data->last_cmd == NULL)
					return (ERR_ALLOC);
			}
		}
	}
	return (SUCCESS);
}

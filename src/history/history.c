/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:28 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/01 20:00:52 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include <readline/history.h>
#include "data_structures.h"

int	ft_add_history(t_minishell *ms_data, char entry[])
{
	char	*last_cmd;

	last_cmd = ms_data->last_cmd;
	if (entry)
	{
		if (!last_cmd || ft_strncmp(entry, last_cmd, ft_strlen(entry) + 1))
		{
			add_history(entry);
			free(last_cmd);
			ms_data->last_cmd = ft_strdup(entry);
			if (ms_data->last_cmd == NULL)
			{
				free(entry);
				ms_data->error = ERR_ALLOC;
				return (ERR_ALLOC);
			}
		}
	}
	return (SUCCESS);
}

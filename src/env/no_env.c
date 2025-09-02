/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:15 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/02 10:43:25 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include "error.h"

static int	check_n_add(t_minishell *ms_data, char *name, char *val)
{
	t_env_lst	*check;
	t_env_lst	*new;

	check = search_env_var(ms_data->env, name);
	if (!check)
	{
		new = new_env_entry(name, val);
		if (!new)
		{
			destroy_env_lst(&ms_data->env);
			return (ERR_ALLOC);
		}
		env_add_back(&ms_data->env, new);
	}
	return (SUCCESS);
}

t_env_lst	**empty_env_check(t_minishell *ms_data)
{
	if (check_n_add(ms_data, "PWD", ms_data->cur_wd))
		return (NULL);
	if (check_n_add(ms_data, "OLDPWD", NULL))
		return (NULL);
	if (check_n_add(ms_data, "SHLVL", "1"))
		return (NULL);
	return (&ms_data->env);
}

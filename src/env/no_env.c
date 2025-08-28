/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:15 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/28 16:32:36 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include "error.h"
#include <limits.h>

static int	add_pwd_no_env(t_minishell *ms_data)
{
	t_env_lst	*check;
	char		*curr_path;

	curr_path = NULL;
	check = search_env_var(ms_data->env, "PWD");
	if (!check)
	{
		curr_path = getcwd(curr_path, PATH_MAX);
		if (!curr_path)
			return (ERR_ALLOC);
		ms_data->cur_wd = curr_path;
		env_add_back(&ms_data->env, new_env_entry("PWD", curr_path));
	}
	return (SUCCESS);
}

t_env_lst	**empty_env_check(t_minishell *ms_data)
{
	t_env_lst	*check;

	if (add_pwd_no_env(ms_data))
		ms_data->error = ERR_ALLOC;
	check = search_env_var(ms_data->env, "OLDPWD");
	if (!check)
		env_add_back(&ms_data->env, new_env_entry("OLDPWD", NULL));
	check = search_env_var(ms_data->env, "SHLVL");
	if (!check)
		env_add_back(&ms_data->env, new_env_entry("SHLVL", "1"));
	return (&ms_data->env);
}

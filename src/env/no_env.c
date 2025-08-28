/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:15 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/26 15:44:37 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "env.h"
#include <limits.h>

static void	add_pwd(t_minishell *ms_data)
{
	t_env_lst	*check;
	char		*curr_path;

	curr_path = NULL;
	curr_path = getcwd(curr_path, PATH_MAX);
	//! check MALLOC
	ms_data->cur_wd = curr_path;
	check = search_env_var(ms_data->env, "PWD");
	if (!check)
		env_add_back(&ms_data->env, new_env_entry("PWD", curr_path));
	// free(curr_path);
}

t_env_lst	**empty_env_check(t_minishell *ms_data)
{
	t_env_lst	*check;

	// check = search_env_var(*env_lst, "?CURRPATH");
	// if (!check)
	add_pwd(ms_data);
	check = search_env_var(ms_data->env, "OLDPWD");
	if (!check)
		env_add_back(&ms_data->env, new_env_entry("OLDPWD", NULL));
	check = search_env_var(ms_data->env, "SHLVL");
	if (!check)
		env_add_back(&ms_data->env, new_env_entry("SHLVL", "1"));
	return (&ms_data->env);
}

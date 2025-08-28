/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:49:52 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/28 22:31:21 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "error.h"
#include "env.h"

// static int	update_env_sys(t_env_lst *env_v, char *new_path, t_env_lst *env);

int	check_dir_access(char *new_path)
{
	if (access(new_path, R_OK | X_OK))
		return (ERR_ARGS);
	return (SUCCESS);
}

int	update_env(char *new_path, t_minishell *ms_data)
{
	t_env_lst	*env_var;

	env_var = search_env_var(ms_data->env, "OLDPWD");
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ms_data->cur_wd;
	}
	else
		free (ms_data->cur_wd);
	ms_data->cur_wd = ft_strdup(new_path);
	if (!ms_data->cur_wd)
		return (ERR_ALLOC);
	env_var = search_env_var(ms_data->env, "PWD");
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(ms_data->cur_wd);
		if (!env_var->value)
			return (ERR_ALLOC);
	}
	return (SUCCESS);
}
